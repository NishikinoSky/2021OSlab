# Lab 0: RV64内核调试

## 1. 实验目的

安装虚拟机及Docker，通过在QEMU模拟器上运行Linux来熟悉如何从源代码开始将内核运行在QEMU模拟器上，学习使用GDB跟QEMU对代码进行联合调试，为后续实验打下基础。

## 2. 实验内容及要求

- 安装虚拟机软件、Ubuntu镜像，自行学习Linux基础命令。
- 安装Docker，下载并导入Docker镜像，创建并运行容器。
- 编译内核并用 gdb + QEMU 调试，在内核初始化过程中设置断点，对内核的启动过程进行跟踪，并尝试使用gdb的各项命令。

## 3. 操作方法和实验步骤

### 3.1 通过虚拟机安装Linux系统

终端命令

| 命令                    | 作用                                                       | 截图                                                         |
| ----------------------- | ---------------------------------------------------------- | ------------------------------------------------------------ |
| pwd                     | 打印出当前工作目录的名称                                   | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/1.jpg" alt="1" style="zoom:75%;" /> |
| ls                      | 打印出当前工作目录的所有内容                               | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/2.png" style="zoom:60%;" /> |
| ls -al                  | 使用长格式打印包括隐藏文件的所有文件及目录信息             | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/3.jpg" style="zoom:50%;" /> |
| cd ~                    | 切换至当前用户目录                                         | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/4.png" style="zoom:75%;" /> |
| mkdir oslab             | 在当前工作目录下创建名为oslab的目录                        | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/5.png" style="zoom:75%;" /> |
| vi test.c               | 用vi编辑器创建并进入名为test.c的文件(vi编辑器命令在此不列) | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/6.png" style="zoom:50%;" /> |
| gedit test.c            | 用gedit编辑器打开test.c文件                                | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/7.jpg" style="zoom:50%;" /> |
| rm test.c               | 删除test.c文件                                             | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/8.png" style="zoom:75%;" /> |
| sudo apt install curl   | 连接服务器安装curl                                         | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/9.png" style="zoom:50%;" /> |
| touch a.txt             | 在当前工作目录创建a.txt文件                                | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/10.png" style="zoom:75%;" /> |
| cat a.txt \| tail -n 10 | 查看a.txt尾部10行的内容                                    | <img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/11.png" style="zoom:75%;" /> |

### 3.2 安装Docker环境并创建容器

1. **安装docker**

```shell
### 使用官方安装脚本自动安装docker
$ curl -fsSL https://get.docker.com | bash -s docker --mirror Aliyun

### 将用户加入docker组，免 sudo
$ sudo usermod -aG docker $USER   ### 注销后重新登陆生效
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/12.png" style="zoom:50%;" />



2. **下载并导入docker镜像**

```shell
### 首先进入oslab.tar所在的文件夹，然后使用该命令导入docker镜像
$ cat oslab.tar | docker import - oslab:2020
### 执行命令后若出现以下错误提示
### ERROR: Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock
### 可以使用下面命令为该文件添加权限来解决
### $ sudo chmod a+rw /var/run/docker.sock

### 查看docker镜像
$ docker image ls
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/13.jpg" style="zoom:75%;" />



3. **从镜像中创建一个容器并进入该容器**

```shell
### 从镜像创建一个容器
$ docker run -it oslab:2020 /bin/bash    ### -i:交互式操作 -t:终端
root@6a50e217856f:/#                     ### 提示符变为 '#' 表明成功进入容器 后面的字符串根据容器而生成，为容器id
root@6a50e217856f:/# exit (或者CTRL+D）   ### 从容器中退出 此时运行docker ps，运行容器的列表为空
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/14.png" style="zoom:75%;" />



```shell
### 查看当前运行的容器
$ docker ps 
### 查看所有存在的容器
$ docker ps -a 
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/15.jpg" style="zoom:75%;" />



```shell
### 启动处于停止状态的容器
$ docker start 6a50     ### 6a50 为容器id的前四位，id开头的几位便可标识一个容器
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/16.jpg" style="zoom:75%;" />



```shell
### 进入已经运行的容器 oslab的密码为2020
$ docker exec -it -u oslab -w /home/oslab 36 /bin/bash
$ docker exec -it 6a50 /bin/bash
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/17.jpg" style="zoom:75%;" />

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/18.png" style="zoom:75%;" />

- `docker run -it oslab:2020 /bin/bash`

  `docker run`指创建一个新的容器并运行一个命令，`-it`指以交互模式运行容器并为容器分配一个伪输入终端，`oslab:2020`为使用的镜像，`/bin/bash`指在容器内执行`/bin/bash`命令

- `docker exec -it -u oslab -w /home/oslab 36 /bin/bash`

  `docker exec`指在运行的容器中执行命令，`-it`指以交互模式运行容器，`-u`为登陆的用户名,`oslab -w /home/oslab` 指定工作目录为/home/oslab，`36`为容器id前2位，`/bin/bash`指在容器内执行`/bin/bash`命令



### 3.3 编译linux内核

```shell
# pwd
/home/oslab
# cd lab0
# export TOP=`pwd`
# mkdir -p build/linux
# make -C linux O=$TOP/build/linux \
          CROSS_COMPILE=riscv64-unknown-linux-gnu- \
          ARCH=riscv CONFIG_DEBUG_INFO=y \
          defconfig all -j$(nproc)
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/18.png" style="zoom:75%;" />

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/19.png" style="zoom:75%;" />



### 3.4 使用QEMU运行内核

```shell
# qemu-system-riscv64 -nographic -machine virt -kernel build/linux/arch/riscv/boot/Image  \
 -device virtio-blk-device,drive=hd0 -append "root=/dev/vda ro console=ttyS0" \
 -bios default -drive file=rootfs.ext4,format=raw,id=hd0 \
 -netdev user,id=net0 -device virtio-net-device,netdev=net0
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/20.png" style="zoom:75%;" />

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/21.png" style="zoom:75%;" />



**退出qemu**

`ctrl+a` `x` 

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/22.png" style="zoom:80%;" />



### 3.5 使用gdb调试内核

**Terminal 1**

```shell
# qemu-system-riscv64 -nographic -machine virt -kernel build/linux/arch/riscv/boot/Image  \
 -device virtio-blk-device,drive=hd0 -append "root=/dev/vda ro console=ttyS0"   \
 -bios default -drive file=rootfs.ext4,format=raw,id=hd0 \
 -netdev user,id=net0 -device virtio-net-device,netdev=net0 -S -s
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/23.png" style="zoom:75%;" />



**Terminal 2**

```shell
# riscv64-unknown-linux-gnu-gdb build/linux/vmlinux
```

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/24.jpg" style="zoom:75%;" />



**执行gdb命令**

```shell
(gdb) target remote localhost:1234
```

- 含义：target remote 命令表示远程调试，而1234是默认的用于调试连接的端口号。
- 执行结果：

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/25.png" style="zoom:75%;" />



```shell
(gdb) b start_kernel 
(gdb) b *0x80000000
(gdb) b *0x80200000
(gdb) info breakpoints
(gdb) delete 2
(gdb) info breakpoints
```

- 含义：

`b start_kernel`指设置断点使程序在调用start_kernel函数时断住

`b *0x80000000`指在地址0x80000000处设置断点

`b *0x80200000`指在地址0x80200000处设置断点

`info breakpoints`指打印所有已设置断点和相关信息

`delete 2`指删除标号为2的断点

- 执行结果：

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/26.png" style="zoom:75%;" />



```shell
(gdb) continue
(gdb) delete 3
(gdb) continue
(gdb) step
(gdb) s
(gdb) (不做输入，直接回车)
(gdb) next
(gdb) n
(gdb) (不做输入，直接回车)
```

- 含义：

`continue`指从断点处继续运行程序

`delete 3`指删除标号为3的断点

`step/s`指单步进入函数内部并执行完

`next/n`指单步执行下一条语句

- 执行结果：

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/27.png" style="zoom:75%;" />



```shell
(gdb) disassemble
(gdb) nexti
(gdb) n
(gdb) stepi
(gdb) s
```

- 含义：

`disassemble`指反汇编pc附近的函数，即start_kernel

`nexti`指单步执行一条机器指令

`stepi`指单步进入一条机器指令

- 执行结果：

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/28.png" style="zoom:75%;" />



<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/29.png" style="zoom:75%;" />

- `nexti/stepi`和`next/step`区别在于前者作用于机器指令层面，后者作用于源码层面；
- `next`和`step`区别在于前者需要单步执行下一条指令，后者单步进入下一条指令



```shell
(gdb) continue
#由于此时无断点，continue将一直执行下去，为了退出gdb，可以：①在gdb中按住ctrl+c退出当前正在运行的gdb命令，然后再用quit退出②在qemu中先按ctrl+a，松开后再按x先退出qemu，然后在gdb中quit退出。
(gdb) quit
```

- 含义：

`quit`退出gdb

- 执行结果：

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/lab0/pic/30.png" style="zoom:75%;" />



## 4. 讨论和心得

注意容器挂载
