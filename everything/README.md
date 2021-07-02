#### powershell  download
1. [powershell文件下载](https://cloud.tencent.com/developer/article/1180302)

#### 窗口置顶

deskpins程序

####  powerhsell文档
[powerhsell文档](https://docs.microsoft.com/zh-cn/powershell/scripting/windows-powershell/install/installing-windows-powershell?view=powershell-7.1)

#### powershell readline更好的命令行体验

	安装(ps版本5.1以上)
	Install-Module -Name PSReadLine -AllowPrerelease -Scope CurrentUser -Force -SkipPublisherCheck
	在profile中引入readline
	# PSReadLine
	Import-Module PSReadLine
	# Enable Prediction History
	Set-PSReadLineOption -PredictionSource History