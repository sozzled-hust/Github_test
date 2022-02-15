# Ros基本操作(rospack/roscd/rosls)

## 1.Using rospack
* **rospack** allows you to get information about packages. In this tutorial, we are only going to cover the find option, which returns the path to package.  
* Usage:

```shell
$ rospack find roscpp
```

would return:

```shell
/opt/ros/melodic/share/roscpp
```

## 2.Using roscd

* **roscd** is part of the rosbash suite. It allows you to change directory (cd) directly to a package or a stack.
* Usage:

```shell
$ roscd roscpp
$ pwd
# should show :/opt/ros/melodic/share/roscpp
```

You can see that YOUR_INSTALL_PATH/share/roscpp is the same path that rospack find gave in the previous example.

* Note that roscd, like other ROS tools, will only find ROS packages that are within the directories listed in your ROS_PACKAGE_PATH. To see what is in your ROS_PACKAGE_PATH, type:

```shell
$ echo $ROS_PACKAGE_PATH
# should show :/opt/ros/melodic/share
```

### 2.1.Subdirectories

* **roscd** can also move to a subdirectory of a package or stack.
* Try:

```shell
$ roscd roscpp/cmake
$ pwd
# should show :/opt/ros/melodic/share/roscpp/cmake
```

### 2.1.roscd log

* **roscd log** will take you to the folder where ROS stores log files. Note that if you have not run any ROS programs yet, this will yield an error saying that it does not yet exist.
* Usage:

```shell
$ roscd log
# should show :No active roscore
```

## 3.Using rosls

* **rosls** is part of the rosbash suite. It allows you to ls directly in a package by name rather than by absolute path.

* Usage:

```shell
$ rosls roscpp_tutorials
# should show :cmake  launch  package.xml  srv
```

## 4.Tab Completion

* It can get tedious to type out an entire package name. In the previous example, roscpp_tutorials is a fairly long name. Luckily, some ROS tools support TAB completion.

```shell
$ roscd roscpp_tut<<< now push the TAB key >>>
# should show : roscpp_tutorials/cmake/   roscpp_tutorials/launch/  roscpp_tutorials/srv/
```

## 5.Review

You may have noticed a pattern with the naming of the ROS tools:

* rospack = ros + pack(age)
* roscd = ros + cd
* rosls = ros + ls

This naming pattern holds for many of the ROS tools.

Now that you can get around in ROS, let's create a package.