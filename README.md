# structree

一个轻量级的，生成树形结构图的工具。

# 如何使用

## 克隆本仓库

```bash
git clone https://github.com/Fantasime/structree.git
cd structree
```

## 构建

```bash
# for Windows
.\build.bat

# for Linux
chmod +x ./build.sh
./build.sh
```

可执行文件将生成在 `structree/bin` 目录中

## 使用

```bash
Usage:
  structree file... [options]
Options:
  -h          Show usage
```

## 语法

树形结构图每一结点的语法可以参照 Markdown 中的标题语法：

`#` 的数量为该结点的层级，`#` 后接该结点的内容

例如:

```markdown
# level 1
## level 2
```

# 示例

将 `structree/examples` 目录下的 `input` 文件输入到 `structree` 中：

```bash
./structree structree/examples/input
```

将会在 `input` 同级目录下生成 `input.structree` 文件，其内容为：

```txt
input
  |
  +-level 1
  |    |
  |    +-level 2
  |    |    |
  |    |    +-level 3
  |    |    |    |
  |    |    |    +-level 4
  |    |    |    |    |
  |    |    |    |    +-level 5
  |    |    |    |    |    |
  |    |    |    |    |    +-level 6
  |    |    |    |    |
  |    |    |    |    +-level 5
  |    |    |    |
  |    |    |    +-level 4
  |    |    |
  |    |    +-level 3
  |    |
  |    +-level 2
  |    |    |
  |    |    +-level 3
  |    |    |    |
  |    |    |    +-level 4
  |    |    |         |
  |    |    |         +-level 5
  |    |    |
  |    |    +-level 3
  |    |
  |    +-level 2
  |
  +-level 1
```

# 关于本仓库

在写作业的时候觉得画树形结构图太麻烦，于是写了这个小玩意。

实际上关于生成树形结构图的算法还有很大的提升空间，以及该程序的拓展性也是很大的。有时间可能会更新本库。















