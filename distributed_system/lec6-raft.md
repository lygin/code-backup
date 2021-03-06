### lec6: Raft

#### 过半票决（Majority Vote）

随着技术的发展，人们发现哪怕网络可能出现故障，可能出现分区，实际上是可以正确的实现能够**自动完成故障切换**的系统。当网络出现故障，将网络分割成两半，网络的两边独自运行，且不能访问对方，这通常被称为网络分区。

在构建能自动恢复，同时又避免脑裂的多副本系统时，人们发现，关键点在于**过半票决（Majority Vote**）。这是Raft论文中出现的，用来构建Raft的一个基本概念。

首先要有奇数个服务器。然后为了完成任何操作，例如Raft的Leader选举，例如提交一个Log条目，**在任何时候为了完成任何操作，你必须凑够过半的服务器来批准相应的操作**。这里的过半是指超过服务器总数的一半。直观来看，如果有3个服务器，那么需要2个服务器批准才能完成任何的操作。

这里背后的逻辑是，**如果网络存在分区，那么必然不可能有超过一个分区拥有过半数量的服务器**。例如，假设总共有三个服务器，如果一个网络分区有一个服务器，那么它不是一个过半的分区。如果一个网络分区有两个服务器，那么另一个分区必然只有一个服务器。因此**另一个分区必然不能凑齐过半的服务器，也必然不能完成任何操作 **(过半是在说所有服务器数量的一半，而不是当前开机服务器数量的一半。)

**如果系统有 2 * F + 1 个服务器，那么系统最多可以接受F个服务器出现故障，仍然可以正常工作。**

这里背后更微妙的点在于，如果你总是需要过半的服务器才能完成任何操作，同时你有一系列的操作需要完成，其中的每一个操作都需要过半的服务器来批准，例如选举Raft的Leader，那么每一个操作对应的过半服务器，**必然至少包含一个服务器存在于上一个操作的过半服务器中。**

也就是说，任意两组过半服务器，至少有一个服务器是重叠的。例如，当一个Raft Leader竞选成功，那么这个Leader必然凑够了过半服务器的选票，而这组过半服务器中，**必然与旧Leader的过半服务器有重叠**。所以，新的Leader必然知道旧Leader使用的任期号（term number），因为新Leader的过半服务器必然与旧Leader的过半服务器有重叠，而旧Leader的过半服务器中的每一个必然都知道旧Leader的任期号。类似的，任何旧Leader提交的操作，必然存在于过半的Raft服务器中，而**任何新Leader的过半服务器中，必然有至少一个服务器包含了旧Leader的所有操作**。这是Raft能正确运行的一个重要因素。

#### Raft简介

Raft会以库（Library）的形式存在于服务中。每个服务的副本将会由两部分组成：应用程序代码和Raft库。**应用程序代码接收RPC**或者其他客户端请求；**不同节点的Raft库**之间相互**合作**，来**维护多副本之间的操作同步**。

从软件的角度来看一个Raft节点，我们可以认为在该节点的上层，是应用程序代码。例如对于Lab 3来说，这部分**应用程序代码**就是一个**Key-Value数据库。**

对于一个Key-Value数据库而言，对应的状态就是Key-Value Table。应用程序往下，就是Raft层。所以，Key-Value数据库需要**对Raft层进行函数调用**，来**传递自己的状态和Raft反馈的信息**。

Raft本身也会保持状态。对我们而言，Raft的状态中，最重要的就是Raft会记录**操作的日志**。

例子：

对于一个拥有**三个副本**的系统来说，很明显我们会有**三个服务器**，这三个服务器有完全一样的结构（上面是应用程序层，下面是Raft层）。理想情况下，也会有**完全相同的数据**分别存在于两层（应用程序层和Raft层）中

除此之外，还有一些客户端，假设我们有了客户端1（C1），客户端2（C2）等等。

客户端就是一些外部程序代码，它们想要使用服务，同时它们不知道，它们正在与一个多副本服务交互。**从客户端的角度来看，这个服务与一个单点服务没有区别。**

**客户端会将请求**发送给当前Raft集群中的**Leader节点对应的应用程序**。这里的请求就是应用程序级别的请求，例如一个访问Key-Value数据库的请求。这些请求可能是Put也可能是Get。

对于一个**单节点的服务**来说，一旦一个Put请求从客户端发送到了服务端，应用程序会**直接执行**这个请求，**更新Key-Value表**，之后返回对于这个**Put请求的响应**。

但是对于一个**基于Raft的多副本服务**，就要复杂一些。

1. 假设客户端将请求发送给Raft的Leader节点，在**服务端程序的内部**，应用程序只会**将来自客户端的请求**对应的操作**向下发送到Raft层**，并且**告知Raft层**，请**1.把这个操作提交到多副本的日志（Log）**中，并在**2.完成时通知我**。

2. 之后，Raft节点之间相互交互，**直到过半的Raft节点将这个新的操作加入到它们的日志（log)**中，也就是说这个操作被过半的Raft节点复制了。

3. 当且仅当Raft的**Leader节点**知道了所以的副本都有了这个操作的拷贝之后。Raft的Leader节点中的**Raft层**，**会向上发送一个通知到应用程序**，也就是Key-Value数据库，来说明：刚刚你提交给我的操作，我**1.已经提交给所有副本**，并且已经**2.成功拷贝给它们**了，现在，你**可以真正的执行这个操作了**（在KV数据库）。

4. 客户端发送请求给Key-Value数据库，这个请求**不会立即被执行**，因为这个请求还没有被拷贝。**当且仅当这个请求存在于过半的副本节点**中时，**Raft**才会**通知Leader节点**，只有在这个时候，**Leader才会实际的执行**这个请求(**提交**）。最终，请求返回给客户端，这就是一个普通请求的处理过程。
5. 当一个操作最终在Leader节点被提交之后，每个副本节点的Raft层会将**相同的操作提交到本地的应用程序层**。在本地的应用程序层，会将这个操作更新到自己的状态。理想情况是**1.所有的副本都有相同的操作序列**，这些操作**2.序列以相同的顺序出现在应用程序的upcall中**，**3.以相同的顺序被本地应用程序应用到本地的状态**。
6. 所有副本节点的状态最终将会是完全一样的。也就是Key-Value数据库的多个副本最终会保持一致

#### Log同步时序

- RPC（Remote Procedure Call）远程过程调用，简单的理解是一个节点请求另一个节点提供的服务

1. 假设客户端将请求发送给服务器1，这里的客户端请求就是一个简单的请求，例如一个Put请求。
2. 之后，服务器1的**Raft层**会**发送一个添加日志（AppendEntries）的RPC到其他两个副本**（S2，S3）。
3. 服务器1会一直等待其他副本节点的响应, 一直等到过半节点的响应返回。这里的过半节点包括Leader自己。所以在一个只有3个副本节点的系统中，Leader只需要等待一个其他副本节点。
4. 当Leader(S1)收到了过半服务器的正确响应，Leader会执行来自客户端的请求(commit给kv数据库)，得到结果，并将结果返回给客户端。与此同时，服务器3可能也会将它的响应返回给Leader，尽管这个响应是有用的，但是这里不需要等待这个响应。
5. 一旦Leader请求**被commit**之后，它需要**将这个消息通知给其他的副本。**通知其他节点副本请求已经被Leader提交。在Raft中，没有明确的committed消息。相应的，committed消息被夹带在下一个AppendEntries消息中，由Leader下一次的AppendEntries对应的RPC发出。

6. 任何情况下，当有了committed消息时，这条消息会填在AppendEntries的RPC中。下一次Leader需要发送心跳，或收到新的客户端请求，要将这个请求同步给其他副本时，Leader会将新的**更大的commit号**随着AppendEntries消息发出，当其他副本收到了这个消息，就知道**之前的commit号**已经**被Leader提交**，**其他副本**接下来也会**执行相应的请求**，**更新本地的状态**。

Attention:

1. 一个客户端响应的背后有多条消息的交互。
2. 其他副本的状态更新不是很及时。实际上，**其他副本（非Leader）执行客户端请求的时间不是很重要**，因为没有人在等这个步骤。例如，客户端就没有等待其他副本执行请求，**客户端只会等待Leader执行请求**。所以，其他副本在什么时候执行请求，不会影响客户端感受的请求时延。

#### 日志（Raft log）

**为什么Raft系统这么关注Log**，**Log究竟起了什么作用？**

1. Log是Leader用来对**操作排序**的一种手段。比如说，我有10个客户端同时向Leader发出请求，Leader必须对这些请求确定一个顺序。实际上，Log是一些按照数字编号的槽位（类似一个数组），槽位的数字表示了Leader选择的顺序。

2. 在一个副本收到了操作，但是还没有执行操作时。该副本需要将这个操作存放在某处，直到收到了Leader发送的新的commit号才执行。所以，对于Raft的Follower来说，Log是用来**存放临时操作**的地方。

3. 用在Leader节点，Leader需要在它的Log中记录操作，因为这些操作可能需要**重传**给Follower。如果一些Follower由于网络原因或者其他原因短时间离线了或者丢了一些消息，Leader需要能够**向Follower重传丢失的Log消息。**所以，Leader也需要一个地方来**存放客户端请求的拷贝**。即使对那些已经commit的请求，为了能够向丢失了相应操作的副本重传。

4. 所有节点都需要保存Log还有一个原因，就是它可以**帮助重启的服务器恢复状态。**需要一个故障了的服务器在修复后，能**重新加入到Raft集群**，要不然你就永远少了一个服务器。对于一个重启的服务器来说，会使用存储在磁盘中的Log。每个Raft节点都需要将Log写入到它的磁盘中，这样它故障重启之后，Log还能保留。而这个Log会被Raft节点用来**从头执行其中的操作进而重建故障前的状态，并继续以这个状态运行。**

#### 应用层接口

1. 第一个接口是key-value层用来**转发客户端请求**的接口。如果客户端发送一个请求给key-value层，key-value层会将这个请求**转发给Raft层**，并说：请将这个请求**存放在Log中的某处**。这个接口实际上是个函数调用，称之为Start函数。这个函数只接收一个参数，就是客户端请求。key-value层说：我接到了这个请求，请把它存在Log中，并在**committed之后告诉我。**

2. 另一个接口是，**Raft层会通知key-value层**：刚刚在Start函数中传给我的**请求已经commit**了。这个向上的接口以go channel中的一条消息的形式存在。Raft层会发出这个消息，key-value层要读取这个消息。所以这里有个叫做**applyCh的channel**，通过它你可以发送ApplyMsg消息。所Start函数的返回需要有足够的信息给key-value层。Start函数的返回值包括，这个**请求将放在Log中的位置（index）**。还会返回当前的**任期号**（term number）和一些其它内容。

**所有的副本**都会收到这个ApplyMsg消息，它们都知道自己应该执行这个请求，弄清楚这个请求的具体含义，并将它应用在本地的状态中。

不同副本的Log或许不完全一样。至少不同副本节点的Log的末尾，会短暂的不同。例如，一个Leader开始发出一轮AppendEntries消息，但是在完全发完之前就故障了。这意味着某些副本收到了这个AppendEntries，并将这条新Log存在本地。而那些没有收到AppendEntries消息的副本，自然也不会将这条新Log存入本地。所以，这里很容易可以看出，**不同副本中Log有时会不一样。**

Raft会最终**强制不同副本的Log保持一致**。或许会有短暂的不一致，但是长期来看，所有副本的Log会被Leader修改，直到Leader确认它们都是一致的。

#### Leader选举

**为什么Raft系统会有个Leader，为什么我们需要一个Leader？**

1. 如果服务器不出现故障，有一个Leader的存在，会使得整个系统更加高效。因为有了一个Leader，对于一个请求，你可以只通过一轮消息就获得过半服务器的认可。对于无Leader的系统，通常需要一轮消息来确认一个临时的Leader，之后第二轮消息才能确认请求。所以，使用一个Leader可以提升系统性能至2倍。
2. Raft生命周期中可能会有不同的Leader，它使用任期号（term number）来区分不同的Leader。Followers不需要知道Leader的ID，它们只需要知道当前的任期号。

**Leader是如何创建出来的呢？**

1. 每个Raft节点都有一个选举定时器（Election Timer），如果在这个定时器时间耗尽之前，当前节点没有收到任何当前Leader的消息，这个节点会认为Leader已经下线，并开始一次选举。有了选举定时器，当**它的时间耗尽时，当前节点会开始一次选举。**

2. 开始一次选举的意思是，当前服务器会**增加任期号**（term number），因为它想成为一个新的Leader。 之后，当前服务器会**发出请求投票**（RequestVote）RPC，消息会**发给所有的Raft节点**。

3. 并不是说如果Leader没有故障就不会有选举。如果Leader没有故障，仍然有可能会有一次新的选举。比如，如果网络很慢，丢了几个心跳，这时，尽管Leader还在运行，可能会有某个选举定时器超时了，进而开启一次新的选举。

4. 如果有一场新的选举，有可能之前的Leader仍然在运行，并认为自己还是Leader。例如，当出现网络分区时，旧Leader始终在一个小的分区中运行，而较大的分区会进行新的选举，最终成功选出一个新的Leader。

**在不知道有新的选举时，旧的Leader会有什么样的行为？**

假设网线故障了，旧的Leader在一个网络分区中，这个网络分区中有一些客户端和少数（未过半）的服务器。在网络的另一个分区中，有着过半的服务器，这些服务器选出了一个新的Leader。

为什么旧的Leader不会执行错误的操作？如果一个Leader在一个网络分区中，并且这个网络分区没有过半的服务器。那么下次客户端发送请求时，这个在少数分区的Leader，它会发出AppendEntries消息。但是因为它在少数分区，**凑不齐过半服务器**，所以永远**不会commit客户端请求**，它永远**不会执行这个请求**，也永远**不会响应客户端**。所以，所以没有客户端会认为这个旧的Leader执行了任何操作。

**如果一次选举成功了，整个集群的节点是如何知道的呢？**

Raft规定，除非是当前任期的Leader，**没人可以发出AppendEntries消息**。所以假设我是一个服务器，我发现对于任期19有一次选举，过了一会我收到了一条AppendEntries消息，这个消息的任期号就是19。那么这条消息告诉我，我不知道的某个节点赢得了任期19的选举。所以，其他服务器通过**接收特定任期号的AppendEntries来知道，选举成功了**。

#### 选举定时器（Election Timer）

任何一条AppendEntries消息都会重置所有Raft节点的选举定时器。这样，只要Leader还在线，并且它还在以合理的速率发出心跳或者其他的AppendEntries消息，Followers收到了AppendEntries消息，会重置自己的选举定时器，这样Leader就可以阻止任何其他节点成为一个候选人。所以只要所有环节都在正常工作，不断重复的心跳会阻止任何新的选举发生。当然，如果网络故障或者发生了丢包，不可避免的还是会有新的选举。

1. Raft通过为选举定时器**随机的选择超时时间**来避免分割选票。

2. 选举定时器的超时时间需要至少大于Leader的心跳间隔。最好选举定时器的**超时时间下限设置成心跳间隔的几倍**

3. 超时时间上限越大，系统的恢复时间也就越长。如果故障很频繁，那么我们就该关心恢复时间有多长。

4. 不同节点的选举定时器的超时**时间差**（S2和S3之间）必须要足够长，使得第一个开始选举的节点能够完成一轮选举。这里**至少需要大于发送一条RPC所需要的往返（Round-Trip）时间**。如果需要10毫秒来发送一条RPC，并从其他所有服务器获得响应。我们需要设置超时时间的上限到足够大，从而使得两个随机数之间的时间差极有可能大于10毫秒。

```
在Lab2中，如果代码不能在几秒内从一个Leader故障中恢复的话，测试代码会报错。所以这种场景下，需要调小选举定时器超时时间的上限。这样才可能在几秒内完成一次Leader选举。
```