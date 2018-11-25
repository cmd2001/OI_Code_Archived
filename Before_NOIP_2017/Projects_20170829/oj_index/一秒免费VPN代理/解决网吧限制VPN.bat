@echo off
@color 2f
@echo        欢迎使用一秒VPN解除网吧禁止VPN程序
@echo          官方网站：www.ymvpn.com
@echo               广告：出售168VPN，如果想购买联系作者。
@echo                 QQ：1260016481 非特殊情况，基本全日在线。
@echo #######################################################
@echo #######      下面将要解除网吧禁止VPN连接        #######
@echo #######  按任意键继续 不想解禁请直接关闭窗口    #######
@echo #######          网吧里一般都可以               #######
@echo #######  如果网吧限制的更死那就没办法了！祝好运 #######
@echo #######################################################
pause
sc config Netman start= AUTO
sc start Netman
sc config rasman start= AUTO
sc start rasman
sc config tapisrv start= AUTO
sc start tapisrv
@echo           解除禁止完成 按任意键退出
@echo #######################################################
pause

exit