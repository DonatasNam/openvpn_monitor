SRC:= monitor_main.c parser.c server_ctrl.c ubus_calls.c
LDFLAGS:= -lubus -lubox -lblobmsg_json

.PHONY: all clean

all: openvpn_monitor

openvpn_monitor: $(SRC)
	$(CC) -g -o $@ $^ $(LDFLAGS)

clean:
	rm -rf openvpn_monitor