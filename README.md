# esp_32_vendor

Extension of esp32 project development ecosystem.

Supports:
1. Automate flashing of more than one esp devices.
2. Override esp-idf example projects by customized projects.
3. do-no-touch code policy on esp-idf example projects.
4. simplified way of defining a multi device project using targets.


Things to try out
1. If user want to control server from android app ?
  1.1 can we integrate onoff client, onoff server model in the same node together with WiFi coexist.
  1.2 through WiFi it will connect to server and get app input and using client it will set on/off.

# diagram

```plantuml

@startuml

 
node "Curtain Module" {
    [Left on_off \nnode] as clnode
    [Right on_off \nnode] as crnode
} 

node "Light Module" {
    [Light1 on_off \nnode] as l1node
    [Light2 on_off \nnode] as l2node
    [Light3 on_off \nnode] as l3node
    [Light4 on_off \nnode] as l4node
}

node "Door Module" {
    [Front door on_off \nnode] as fdnode
    [Rear door on_off \nnode] as rdnode
}

node "Window Module" {
    [Window1 on_off \nnode] as w1node
    [Window2 on_off \nnode] as w2node
} 

node "Provisioner Module" {
}

node "Client Module" {
}

[Client Module] -up-> [Light Module]
[Client Module] -up-> [Door Module]
[Client Module] -up-> [Window Module]
[Client Module] -up-> [Curtain Module]

@enduml