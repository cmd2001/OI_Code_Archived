firewall-cmd --zone=public --add-port=80/tcp --permanen
firewall-cmd --zone=public --add-port=2222/tcp --permanen
firewall-cmd --zone=public --add-port=2334/tcp --permanen
firewall-cmd --reload
useradd -u 544 -d /home/Cmd2001 -g sudo -m  Cmd2001
