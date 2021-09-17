---
title: powershell工具
date: 2021-09-17 17:05:29
tags: 
  - 命令行
  - windows
  - powershell
categories:
  - [术,命令行,工具]
---

## powershell 命令工具

用惯了bash的sed,grep ,awk,再用powershell处理流式文本感觉十分难受.在某一个摸鱼的下午自己琢磨了一下(指google).发现在powershell上也可以使用这些工具.

### 安装包管理工具scoop

scoop是一个强大的windows命令行包管理工具,[github项目地址](https://github.com/lukesampson/scoop)

#### 安装前环境准备

- Windows 7 SP1+ / Windows Server 2008+
- [PowerShell 5](https://aka.ms/wmf5download) (or later, include [PowerShell Core](https://docs.microsoft.com/en-us/powershell/scripting/install/installing-powershell-core-on-windows?view=powershell-6)) and [.NET Framework 4.5](https://www.microsoft.com/net/download) (or later)
- PowerShell must be enabled for your user account e.g. `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser`

安装

```powershell
Invoke-Expression (New-Object System.Net.WebClient).DownloadString('https://get.scoop.sh')
#或者使用以下命令
iwr -useb get.scoop.sh | iex  #iwr是Invoke-WebRequest 命令别名 iex命令为invove-expression的别名：接收一个字符串作为要运行的完整命令（包括参数）。
```

安装会自动设置环境变量,十分方便

## 使用scoop

#### 下载安装软件

若想查找软件,直接运行以下命令,例如查找awk

```powershell
PS D:\> scoop search awk
#输出:
'extras' bucket:
    bizhawk (2.6.2)

'main' bucket:
    busybox (4264-gc79f13025) --> includes 'awk'
    czkawka-cli (2.0.0)
    czkawka (3.2.0)
    gawk (5.1.0)
    gow (0.8.0) --> includes 'awk.exe'
    unxutils (2007.03.01) --> includes 'gawk.exe'
 
#此时若想安装,直接安装对应的包即可
#例如,安装busybox包
scoop install busybox
```

#### 一些其他使用注意

##### 配置环境变量改变软件安装位置

##### Install Scoop to a Custom Directory by changing `SCOOP`

```powershell
$env:SCOOP='D:\Applications\Scoop'
[Environment]::SetEnvironmentVariable('SCOOP', $env:SCOOP, 'User')
# run the installer
```

##### Configure Scoop to install global programs to a Custom Directory by changing `SCOOP_GLOBAL`

```powershell
$env:SCOOP_GLOBAL='D:\GlobalScoopApps'
[Environment]::SetEnvironmentVariable('SCOOP_GLOBAL', $env:SCOOP_GLOBAL, 'Machine')
# run the installer
```

##### 添加仓库

> scoop自带的main bucket软件过少，我们需要添加extra bucket

```powershell
scoop bucket add <仓库名>
```

**仓库列表**

> 输入 `scoop bucket known` 就能查看官方已知的存储桶列表

```json
    "extras": "https://github.com/lukesampson/scoop-extras.git",
    "versions": "https://github.com/scoopinstaller/versions",
    "nightlies": "https://github.com/scoopinstaller/nightlies",
    "nirsoft": "https://github.com/kodybrown/scoop-nirsoft",
    "php": "https://github.com/nueko/scoop-php.git",
    "nerd-fonts": "https://github.com/matthewjberger/scoop-nerd-fonts.git",
    "nonportable": "https://github.com/oltolm/scoop-nonportable",
    "java": "https://github.com/se35710/scoop-java",
    "games": "https://github.com/Calinou/scoop-games"
```

#### 常用命令

> 使用scoop help查看命令

```
alias          Manage scoop aliases
bucket         Manage Scoop buckets
cache          Show or clear the download cache
checkup        Check for potential problems
cleanup        Cleanup apps by removing old versions
config         Get or set configuration values
create         Create a custom app manifest
depends        List dependencies for an app
export         Exports (an importable) list of installed apps
help           Show help for a command
hold           Hold an app to disable updates
home           Opens the app homepage
info           Display information about an app
install        Install apps
list           List installed apps
prefix         Returns the path to the specified app
reset          Reset an app to resolve conflicts
search         Search available apps
status         Show status and check for new app versions
unhold         Unhold an app to enable updates
uninstall      Uninstall an app
update         Update apps, or Scoop itself
virustotal     Look for app's hash on virustotal.com
which          Locate a shim/executable (similar to 'which' on Linux)

常用命令
scoop help            #帮助
scoop list            #查看当前已安装软件
scoop info app        #查看软件信息
scoop install app     #安装软件
scoop search app      #搜索软件
scoop uninstall app   #卸载软件
scoop update app      #更新指定软件
scoop update *        #更新安装的软件和scoop

# 设置代理(http)
scoop config proxy 127.0.0.1:4412
```

