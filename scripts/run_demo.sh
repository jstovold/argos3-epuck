screen -dmS 73
screen -dmS 80
screen -dmS 81
screen -dmS 84
screen -dmS 86
screen -dmS 89


screen -S 73 -X stuff "ssh root@192.168.1.73 '/home/root/collision'\n"
screen -S 80 -X stuff "ssh root@192.168.1.80 '/home/root/collision'\n"
screen -S 81 -X stuff "ssh root@192.168.1.81 '/home/root/collision'\n"
screen -S 84 -X stuff "ssh root@192.168.1.84 '/home/root/collision'\n"
screen -S 86 -X stuff "ssh root@192.168.1.86 '/home/root/collision'\n"
screen -S 89 -X stuff "ssh root@192.168.1.89 '/home/root/collision'\n"

