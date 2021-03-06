### lec7:raft

#### 日志恢复

1. AppendEntries消息实际上有两条，因为要发给两个Followers。它们包含了客户端发送给Leader的请求。我们现在想将这个请求复制到所有的Followers上。这里的AppendEntries RPC还包含了prevLogIndex字段和prevLogTerm字段。所以Leader在发送AppendEntries消息时，**会附带前一个槽位的信息。**
2. Followers在收到AppendEntries消息时，可以知道它们收到了一个带有若干Log条目的消息，并且是从槽位13开始。Followers在写入Log之前，会**检查本地的前一个Log条目，是否与Leader发来的有关前一条Log的信息匹配。**

3. 如果Follower发现不匹配，会拒绝这个AppendEntries，并返回False给Leader
4. 为了响应Followers返回的拒绝，Leader会减小对应的nextIndex。所以它现在减小了两个Followers的nextIndex
5. 如果接受一个AppendEntries消息，那么需要首先删除本地相应的Log，再用AppendEntries中的内容替代本地Log。这个时候，Folloer和leader之间的Log保持了一致。
6. 而Leader在收到了Followers对于AppendEntries的肯定的返回之后，它会增加相应的nextIndex。

**总结：Leader使用了一种备份机制来探测Followers的Log中，第一个与Leader的Log相同的位置。在获得位置之后，Leader会给Follower发送从这个位置开始的，剩余的全部Log。经过这个过程，所有节点的Log都可以和Leader保持一致。**

我们擦除了一些Log条目，为什么Raft系统可以安全的删除这条记录？毕竟我们在删除这条记录时，某个相关的客户端请求也随之被丢弃了。

这条Log条目并没有存在于过半服务器中，因此无论之前的Leader是谁，发送了这条Log，它都没有得到过半服务器的认可。因此旧的Leader**不可能commit了这条记录**，也就**不可能将它应用**到应用程序的状态中，进而也就**不可能回复给客户端**说请求成功了。并且如果客户端发送请求之后一段时间没有收到回复，它应该重新发送请求。所以我们知道，不论这个被丢弃的请求是什么，我们都没有执行它，没有把它包含在任何状态中，并且客户端之后会重新发送这个请求。

#### 选举限制

Raft有一个稍微复杂的选举限制（Election Restriction）。这个限制要求，在处理别节点发来的RequestVote RPC时，需要做一些检查才能投出赞成票。这里的限制是，节点只能向满足下面条件之一的候选人投出赞成票：

1. 候选人最后一条Log条目的任期号**大于**本地最后一条Log条目的任期号；
2. 候选人最后一条Log条目的任期号**等于**本地最后一条Log条目的任期号，且候选人的Log记录长度**大于等于**本地Log记录的长度

所以在这里，Raft更喜欢拥有**任期号更高**的**旧Leader记录**的候选人。限制2说明，如果候选人都拥有**任期号最高**的旧Leader记录，那么Raft更喜欢**拥有更多记录**的候选人。

#### 快速恢复

如果一个Follower关机并错过了1000条Log条目，Leader重启之后，需要每次通过一条RPC来回退一条Log条目来遍历1000条Follower错过的Log记录。

所以，为了能够更快的恢复日志，这里的大致思想是，让Follower返回足够的信息给Leader，这样Leader可以**以任期（Term）为单位来回退**，而**不用每次只回退一条Log条目**。所以现在，在恢复Follower的Log时，如果Leader和Follower的Log不匹配，Leader只需要**对每个不同的任期发送一条AppendEntries**，而不用对每个不同的Log条目发送一条AppendEntries。这只是一种加速策略，当然，也可以想出许多其他不同的日志恢复加速策略。

可以让Follower在回复Leader的AppendEntries消息中，携带3个额外的信息，来加速日志的恢复。回复是指，Follower因为Log信息不匹配，拒绝了Leader的AppendEntries之后的回复。这里的三个信息是指：

- XTerm：这个是Follower中与Leader**冲突的Log对应的任期号**。Leader会在prevLogTerm中带上本地Log记录中，前一条Log的任期号。如果Follower在对应位置的任期号不匹配，它会拒绝Leader的AppendEntries消息，并将自己的任期号放在XTerm中。如果Follower在对应位置没有Log，那么这里会返回 -1。
- XIndex：这Follower中对应任期号为XTerm的**第一条Log条目的槽位号。**

- XLen：如果Follower在对应位置没有Log，那么XTerm会返回-1，XLen表示空白的Log槽位数。

```
为了通过Lab2的测试，肯定需要做一些优化工作。Lab2的测试用例中，有一件不幸但是不可避免的事情是，它们需要一些实时特性。这些测试用例不会永远等待你的代码执行完成并生成结果。所以有可能你的方法技术上是对的，但是花了太多时间导致测试用例退出。因此需要关注性能，从而使得方案即是正确的，又有足够的性能。
```

#### 持久化（Persistence）

有些数据被标记为持久化的（Persistent），有些信息被标记为非持久化的（Volatile）。持久化和非持久化的区别只在服务器重启时重要。当你更改了被标记为持久化的某个数据，服务器应该将更新写入到磁盘，或者其它的持久化存储中。

持久化的存储可以确保当服务器重启时，服务器可以找到相应的数据，并将其加载到内存中。这样可以使得服务器在故障并重启后，继续重启之前的状态。

在Raft论文有且仅有三个数据是需要持久化存储的。它们分别是**Log、currentTerm、votedFor**。Log是所有的Log条目。当某个服务器刚刚重启，在它加入到Raft集群之前，它必须要检查并确保这些数据有效的存储在它的磁盘上。服务器必须要有某种方式来发现，自己的确有一些持久化存储的状态，而不是一些无意义的数据。

1. Log需要被持久化存储的原因是，这是唯一记录了应用程序状态的地方。Raft论文没有要求我们持久化存储应用程序状态。假如我们运行了一个数据库服务，实际的数据库并不会被持久化存储，只有Raft的Log被存储了。所以当服务器重启时，唯一能用来重建应用程序状态的信息就是存储在Log中的一系列操作，所以Log必须要被持久化存储。
2. votedFor用来确保每个任期只有最多一个Leader。在一个故障的场景中，如果一个服务器收到了一个RequestVote请求，并且为服务器1投票了，之后它故障。如果它没有存储它为哪个服务器投过票，当它故障重启之后，收到了来自服务器2的同一个任期的另一个RequestVote请求，那么它还是会投票给服务器2，因为它发现自己的votedFor是空的，因此它认为自己还没投过票。现在这个服务器，在同一个任期内同时为服务器1和服务器2投了票。因为服务器1和服务器2都会为自己投票，它们都会认为自己有过半选票（3票中的2票），那它们都会成为Leader。现在同一个任期里面有了两个Leader。这就是为什么votedFor必须被持久化存储。
3. currentTerm实际上还是为了实现一个任期内最多只有一个Leader。如果重启之后我们不知道任期号是什么，很难确保一个任期内只有一个Leader。

这些数据需要在每次你修改它们的时候存储起来。安全的做法是**每次你添加一个Log条目**，更新currentTerm或者更新votedFor，都需要持久化存储这些数据。在一个真实的Raft服务器上，这意味着将数据写入磁盘，所以需要一些文件来记录这些数据。

如果直到服务器与外界通信时，才有可能持久化存储数据，那么可以通过批量操作来提升性能。例如，只在服务器回复一个RPC或者发送一个RPC时，服务器才进行持久化存储，这样可以节省一些持久化存储的操作。

这很重要是因为，**向磁盘写数据是一个代价很高的操作**。如果是一个机械硬盘，我们通过写文件的方式来持久化存储，向磁盘写入任何数据都需要花费大概10毫秒时间。所以这里的持久化操作的代价可能会非常非常高。这些操作可能成为**限制性能的因素**，因为在这些Raft服务器上执行任何操作，都需要10毫秒。而10毫秒相比发送RPC或者其他操作来说都太长了。如果持久化存储在一个机械硬盘上，那么每个操作至少要10毫秒，这意味着永远也不可能构建一个每秒能处理超过100个请求的Raft服务。这就是所谓的synchronous disk updates的代价。

**优化磁盘写入性能是一个出现在所有系统中的常见的问题，也必然出现在Raft中。**

1. 如果你想构建一个能每秒处理超过100个请求的系统，可以构建一个电池供电的DRAM，然后在这个电池供电的DRAM中做持久化存储。这样，如果Server重启了，存储在RAM中的数据还能保存。那么持久化存储就不再会是一个性能瓶颈。所以，synchronous disk updates是为什么数据要区分持久化和非持久化（而非所有的都做持久化）的原因就是越少数据持久化，就有越高的性能。

```
当你持久化存储一个Log或者currentTerm，这些数据是否实时的存储在磁盘中，你该怎么做来确保它们在那呢？
在一个UNIX或者一个Linux或者一个Mac上，为了调用系统写磁盘的操作，只需要调用write函数，在write函数返回时，并不能确保数据存在磁盘上，并且在重启之后还存在。所以，如果在UNIX上，调用了write，将一些数据写入之后，需要调用fsync。fsync可以确保在返回时，所有之前写入的数据已经安全的存储在磁盘的介质上了。fsync是一个代价很高的调用，这也是为什么write不负责将数据写入磁盘，fsync负责将数据写入磁盘。因为写入磁盘的代价很高，你永远也不会想要执行这个操作，除非你想要持久化存储一些数据。
```

2. 另一个常见方法是，**批量执行操作**。

如果有大量的客户端请求，应该同时接收它们，但是先不返回。**等大量的请求累积之后，一次性持久化存储（比如）100个Log**，之后再发送AppendEntries。**Leader收到了一个客户端请求，在发送AppendEntries RPC给Followers之前，必须要先持久化存储在本地。**因为Leader必须要commit那个请求，并且不能忘记这个请求。实际上，**在回复AppendEntries 消息之前，Followers也需要持久化存储这些Log条目到本地**，因为它们最终也要commit这个请求，它们不能因为重启而忘记这个请求。

另外，Raft论文假设，应用程序状态会随着重启而消失。所以既然Log已经持久化存储了，那么应用程序状态就不必再持久化存储。因为Log从系统运行的初始就被持久化存储下来。所以，当Leader重启时，Leader会从第一条Log开始，执行每一条Log条目，并提交给应用程序。所以，重启之后，**应用程序**可以通过**执行每一条Log来完全从头构建自己的状态**。这是一种简单且优雅的方法，但是很明显**会很慢。**

#### 日志快照（Log Snapshot）

在Raft中，Log压缩和快照解决的问题是：对于一个长期运行的系统，例如运行了几周，几个月甚至几年，如果我们按照Raft论文规则，那么**Log会持续增长。最后可能会有数百万条Log**，从而需要大量的内存来存储。如果持久化存储在磁盘上，最终会消耗磁盘的大量空间。如果一个服务器重启了，它需要通过重新从头开始执行这数百万条Log来重建自己的状态。当故障重启之后，**遍历并执行整个Log的内容可能要花费几个小时来完成**。

为了应对这种场景，Raft有了快照（Snapshots）的概念。快照背后的思想是，**要求应用程序将其状态的拷贝作为一种特殊的Log条目存储下来**。我们之前几乎都忽略了应用程序，但是事实是，假设我们基于Raft构建一个key-value数据库，Log将会包含一系列的Put/Get或者Read/Write请求。

这里有个有趣的事实，那就是：对于大多数的应用程序来说，**应用程序的状态远小于Log的大小**。在某些时间点，Log和应用程序的**状态是可以互换**的，它们是用来表示应用程序状态的不同事物。但是**Log可能包含大量的重复的记录**（例如对于X的重复赋值），这些记录使用了Log中的大量的空间，但是同时却压缩到了key-value表单中的一条记录。这在多副本系统中很常见。在这里，如果存储Log，可能尺寸会非常大，相应的，如果**存储key-value表单，这可能比Log尺寸小得多**。这就是快照的背后原理。

当Raft认为它的Log将会过于庞大，例如大于10MB或者任意的限制，Raft会要求应用程序在Log的特定位置，对其状态做一个快照。所以，如果Raft要求应用程序做一个快照，Raft会**从Log中选取一个与快照对应的点**，然后**要求应用程序在那个点的位置做一个快照**。这里极其重要，因为我们接下来将会**丢弃所有那个点之前的Log记录**。如果我们有一个点的快照，那么我们可以**安全的将那个点之前的Log丢弃**。（在key-value数据库的例子中）**快照本质上就是key-value表单**。

只要Raft持久化存储了快照，快照对应的Log槽位号，那么快照对应槽位号之前的这部分Log可以被丢弃，我们将不再需要这部分Log。

Raft快照的工作原理：**Raft要求应用程序做快照**，**得到快照之后将其存储在磁盘中**，同时**持久化存储快照之后的Log**，并**丢弃快照之前的Log**。所以，Raft的持久化存储实际上是持久化应用程序快照，和快照之后的Log。

**问题：**

这里丢弃了快照之前的Log，引入了大量的复杂性。如果有的Follower的Log较短，在Leader的快照之前就结束，那么那个Follower永远也不可能恢复完整的Log。因为，如果一个Follower只有前两个槽位的Log，Leader不再有槽位3的Log可以通过AppendEntries RPC发给Follower，Follower的Log也就不可能补齐至Leader的Log。

Raft选择的解决方法是，Leader可以丢弃Follower需要的Log。所以，需要某种机制让AppendEntries能处理某些Follower Log的结尾到Leader Log开始之间丢失的这一段Log。解决方法是（一个新的消息类型）InstallSnapshot RPC。

当Follower刚刚恢复，如果它的Log短于Leader通过 AppendEntries RPC发给它的内容，那么它首先会强制Leader回退自己的Log。在某个点，Leader将不能再回退，因为它已经到了自己Log的起点。这时，Leader会将自己的快照发给Follower，之后立即通过AppendEntries将后面的Log发给Follower。

不幸的是，这里明显的增加了的复杂度。因为这里需要Raft组件之间的协同，这里还有点违反模块性，因为这里需要组件之间有一些特殊的协商。例如，当Follower收到了InstallSnapshot，这个消息是被Raft收到的，但是Raft实际需要应用程序能吸纳这个快照。所以它们现在需要更多的交互了。

#### 线性一致

通常来说，**线性一致等价于强一致**。一个服务是线性一致的，那么它**表现的就像只有一个服务器**，并且服务器没有故障，这个服务器每次执行一个客户端请求，并且没什么奇怪的是事情发生。

一个系统的执行历史是一系列的客户端请求。如果**执行历史**按照一个顺序排列，且**排列顺序与客户端请求的实际时间相符合**，那么它是线性一致的。每一个读操作都看到的是最近一次写入的值。

要达到线性一致，要确定顺序，有两个限制条件：

1. 如果一个操作在另一个操作开始前就结束了，那么这个操作必须在执行历史中出现在另一个操作前面。
2. 执行历史中，读操作，必须在相应的key的写操作之后。

我们将这些箭头展平成一个线性一致顺序来看看真实的执行历史，我们可以发现总的执行历史是线性一致的。（这里可以这么理解，左边是一个多副本系统的输入输出，因为分布式程序或者程序的执行，产生了这样的时序，但是在一个线性一致的系统中，实际是按照右边的顺序执行的操作。**左边是实际时钟**，**右边是逻辑时钟**。）

