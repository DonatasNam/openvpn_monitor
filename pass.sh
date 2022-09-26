#!/bin/bash
cd $HOME/Documents/rutx_src
make  package/openvpn_monitor/compile V=s
cd $HOME/Documents/rutx_src/bin/packages/arm_cortex-a7_neon-vfpv4/base
sshpass -p Admin123 scp openvpn_monitor_1.0.0-1_arm_cortex-a7_neon-vfpv4.ipk root@192.168.1.1:/tmp


