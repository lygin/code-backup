### lec3：GFS

构建分布式系统大多都是关于如何设计存储系统，或是设计其它基于大型分布式存储的系统。所以我们会更加关注如何为大型分布式存储系统设计一个优秀的接口，以及如何设计存储系统的内部结构，这样系统才能良好运行

```
阅读GFS论文
```

人们设计大型分布式系统或大型存储系统出发点通常是，他们想获取巨大的性能加成，进而利用数百台计算机的资源来同时完成大量工作。

很自然的想法就是将数据分割放到大量的服务器上，这样就可以并行的从多台服务器读取数据。我们将这种方式称之为**分片（Sharding）**。

如果在成百上千台服务器进行分片，将会看见常态的故障。如果有数千台服务器，那么总是会有一台服务器宕机，每天甚至每个小时都可能会发生错误。所以，我们需要自动化的方法而不是人工介入来修复错误。我们需要一个**自动的容错系统**，这就引出了容错这个话题（fault tolerance）。

**实现容错**最有用的一种方法是**使用复制**，只需要**维护2-3个数据的副本**，当其中一个故障了，你就可以使用另一个。所以，如果想要容错能力，就得有复制（replication）。

如果有复制，那就有了两份数据的副本。所以，有了两个数据副本，可以任意使用其中一个副本来容错。但是如果你不够小心，两个数据的副本就不是完全一致，严格来说，它们就**不再互为副本**了。而你获取到的数据内容也将取决于你向哪个副本请求数据。这对于应用程序来说就有些麻烦了。所以，如果我们有了复制，我们就有**不一致的问题（inconsistency）**。

通过聪明的设计，你可以避免不一致的问题，并且让数据看起来也表现的符合预期。但是为了达到这样的效果，你总是需要额外的工作，需要不同**服务器之间通过网络额外的交互**，而这样的交互会降低性能。

#### GFS

Google有大量的数据，需要大量的磁盘来存储这些数据，并且需要能借助MapReduce这样的工具来快速处理这些数据。所以，Google需要能够快速的并行访问这些海量数据。

Google的目标是构建一个大型的，快速的文件系统。并且这个文件系统是全局有效的，这样各种不同的应用程序都可以从中读取数据。全局通用的存储系统，那就意味着如果我存储了大量从互联网抓取的数据，你也可以通过申请权限来查看这些数据，因为我们都使用了同一个存储系统。

```
FAST,BIG,GLOBAL
```

为了获得**大容量和高速**的特性，每个包含了数据的文件会**被GFS自动的分割并存放在多个服务器**之上，这样读写操作自然就会变得很快。因为可以从多个服务器上同时读取同一个文件，进而获得更高的聚合吞吐量。将文件分割存储还可以在存储系统中保存比单个磁盘还要大的文件。

1.GFS被设计成只在一个数据中心运行，所以这里并没有将副本保存在世界各地

2.GFS并不面向普通的用户，这是一个Google内部使用的系统

3.GFS在各个方面**对大型的顺序文件读写**做了定制。GFS是为TB级别的文件而生。并且GFS只会顺序处理，不支持随机访问。某种程度上来说，它有点像**批处理**的风格。GFS并没有花费过多的精力来降低延迟，它的关注点在于巨大的吞吐量上，所以单次操作都涉及到MB级别的数据。

4.论文也提出了一个当时非常异类的观点：存储系统具有**弱一致性**也是可以的。GFS并不保证返回正确的数据，借助于这一点，GFS的目标是提供更好的性能。

5.在一些学术论文中，你或许可以看到一些容错的，多副本，自动修复的多个Master节点共同分担工作，但是GFS却宣称使用**单个Master节点**并能够很好的工作。

```
如果GFS返回错误的数据，会不会影响应用程序？
如果通过搜索引擎做搜索，20000个搜索结果中丢失了一条或者搜索结果排序是错误的，没有人会注意到这些。这类系统对于错误的接受能力好过类似于银行这样的系统。
另外，尽管GFS可能会返回错误的数据，但是可以在应用程序中做一些补偿。论文中提到，应用程序应当对数据做校验，并明确标记数据的边界，这样应用程序在GFS返回不正确数据时可以恢复。
```

#### GFS: Master节点

假设我们有上百个客户端和一个Master节点。尽管实际中可以拿多台机器作为Master节点，但是GFS中Master是Active-Standby模式，所以只有一个Master节点在工作。**Master节点保存了文件名和存储位置的对应关系**。还有大量的Chunk服务器，可能会有数百个。在这里，**Master节点用来管理文件和Chunk的信息**，而**Chunk服务器用来存储实际的数据**。

Master节点知道**每一个文件**对应的**所有的Chunk的ID**，这些Chunk每个是64MB大小，**它们共同构成了一个文件**。如果我有一个1GB的文件，那么Master节点就知道文件的第一个Chunk存储在哪，第二个Chunk存储在哪，等等。当我想读取这个文件中的任意一个部分时，我需要向Master节点查询对应的Chunk在哪个服务器上，之后我可以直接从Chunk服务器读取对应的Chunk数据。

GFS的一致性以及GFS是如何处理故障。为了了解这些，我们需要知道Master节点内保存的数据内容，这里我们关心的主要是两个表单：

- 第一个是**文件名到Chunk ID或者Chunk Handle数组的对应**。这个表单告诉你，文件对应了哪些Chunk。但是只有Chunk ID是做不了太多事情的，所以有了第二个表单。

- 第二个表单记录了Chunk ID到Chunk数据的对应关系。这里的数据又包括了：

  1.每个Chunk存储在哪些服务器上，Chunk服务器的列表

  2.每个Chunk对应的版本号。

  3.所有**对于Chunk的写操作都必须在主Chunk上顺序处理**，主Chunk是Chunk的多个副本之一。Chunk服务器持有主Chunk。

  4.**主Chunk只能在特定的租约时间内担任主Chunk**，主Chunk的租约过期时间。

为了能让Master重启而不丢失数据，Master节点会同时将数据存储在磁盘上。所以Master节点读数据只会从内存读，但是写数据的时候，至少有一部分数据会接入到磁盘中。更具体来说，**Master会在磁盘上存储log**，每次有**数据变更**时，Master**会在磁盘的log中追加一条记录**，并生成CheckPoint（类似于备份点）。

需要存在磁盘上:标记成NV（non-volatile, 非易失），这个标记表示对应的数据会写入到磁盘上。

1.Chunk Handle的数组（第一个表单）

2.版本号

不需要存在磁盘上:V

1.Chunk服务器列表。Master节点重启之后可以与所有的Chunk服务器通信，并查询每个Chunk服务器存储了哪些Chunk。

2.主Chunk的ID。Master节点重启之后会忘记谁是主Chunk，它只需要等待60秒租约到期，那么它知道对于这个Chunk来说没有主Chunk，这个时候，Master节点可以安全指定一个新的主Chunk。

3.租约过期时间

任何时候，如果文件扩展到达了一个新的64MB，需要**新增一个Chunk**或者由于指定了**新的主Chunk**而导致**版本号更新**了，Master节点需要**向磁盘中的Log追加一条记录**说，我刚刚向这个文件**添加了一个新的Chunk**或者我刚刚**修改了Chunk的版本号**。所以每次有这样的更新，都需要写磁盘。

```
这里在磁盘中维护log而不是数据库的原因是，数据库本质上来说是某种B树（b-tree）或者hash table，相比之下，追加log会非常的高效，因为可以将最近多个log记录一次性写入磁盘。因为数据都是向同一个地址追加，只需要等待磁盘的磁碟旋转一次。而对于B树来说，每一份数据都需要在磁盘中随机位置写入。所以使用Log可以使得磁盘写入更快一些。
```

#### GFS: 写文件

对于读文件来说，可以从任何最新的Chunk副本读取数据，但是对于写文件来说，**必须要通过Chunk的主副本**（Primary Chunk）来写入。

对于某个特定的Chunk来说，在某一个时间点，Master不一定指定了Chunk的主副本。所以，写文件的时候，需要考虑Chunk的主副本不存在的情况。

对于Master节点来说，如果发现Chunk的主副本不存在，Master会找出所有**存有Chunk最新副本的Chunk服务器**。

第一步找出最新的Chunk副本。是**在Master节点发生**，因为，现在是客户端告诉Master节点说要追加某个文件，Master节点需要告诉客户端向哪个Chunk服务器（Primary Chunk所在的服务器）去做追加操作。Master节点的工作就是弄清楚在追加文件时，客户端应该与哪个Chunk服务器通信。

每个Chunk可能同时有多个副本，**最新的副本**是指，**副本中保存的版本号与Master中记录的Chunk的版本号一致**。Chunk副本中的版本号是由Master节点下发的，所以Master节点知道，对于一个特定的Chunk，哪个版本号是最新的。这就是为什么Chunk的版本号在Master节点上需要保存在磁盘这种非易失的存储中的原因，因为如果版本号在故障重启中丢失，且部分Chunk服务器持有旧的Chunk副本，这时，Master是没有办法区分哪个Chunk服务器的数据是旧的，哪个Chunk服务器的数据是最新的。

之所以要管理Chunk的版本号，是因为这样Master可以将实际更新Chunk的能力转移给Primary服务器。并且在将版本号更新到Primary和Secondary服务器之后，如果Master节点故障重启，还是可以在相同的Primary和Secondary服务器上继续更新Chunk。

#### GFS: 一致性

GFS设计成多个副本不一致，弱一致性。

要让副本保持同步，其中一条规则就是你们不能允许这种只更新部分服务器的不完整操作。这意味着，你必须要有某种机制，即使客户端挂了，系统仍然会完成请求。

时不时的，Secondary之间可能会有差异，比如客户端从Master节点获取的是稍微过时的Secondary。

为了实现强一致，就是需要在系统中修复的东西，它们增加了系统的复杂度，增加了系统内部组件的交互，在lab2，3中会建立一个强一致系统。

#### 局限性：

GFS最严重的局限可能在于，它只有一个Master节点，会带来以下问题：

1.Master节点必须为每个文件，每个Chunk维护表单，随着GFS的应用越来越多，这意味着涉及的文件也越来越多，最终Master会耗尽内存来存储文件表单。你可以增加内存，但是单台计算机的内存也是有上限的。

2.单个Master节点要承载数千个客户端的请求，而Master节点的CPU每秒只能处理数百个请求，尤其Master还需要将部分数据写入磁盘，客户端数量超过了单个Master的能力

3.应用程序发现很难处理GFS奇怪的语义（GFS的副本数据的同步，或者可以说不同步）

4.Master节点的故障切换不是自动的。GFS需要人工干预来处理已经永久故障的Master节点，并更换新的服务器