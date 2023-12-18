# esp_32_vendor

Extension of esp-idf project development ecosystem.

Supports:

1. Automate flashing of more than one esp devices.
2. Override esp-idf example projects by customized projects.
3. do-no-touch code policy on esp-idf example projects.
4. simplified way of defining a multi device project using targets.

![Domain model in PlantUML](http://www.plantuml.com/plantuml/png/TTB1IWCn40RWUvvYwBs7RdkMGiLJ1V7YeIwoc4G3wOpC9lOWlhkawKeI9hSm--tEdv_Tps7Y4CzUAL18si3g43bC3k6HTFHc1JyA0E1qD3O0uHjP2w-Ow0ZJ3Ey-7JDvTX-Vek6h-GLrMt6ymdP16cw4r_qc7GiqI6Xeq5P2smRj9BJBQPUmzqJSPdrWmW2QY8KFM5rKOYRkETRreXU7cYxjgZoLUhdaNWerI6feodzY-dQp8pJbjVvJ7Bmp6EedfseumZf-hUzk5Ix37YhgwvhgvbrL_vYZKdk3Efxz7m00)


| Group Name           | Group Address |
| -------------------- | ------------- |
| Light Module         | 0xC000        |
| Window Module        | 0xC200        |
| Light Module         | 0xC400        |
| Curtain Module       | 0xC600        |
| Door Module          | 0xC800        |
| Climate Module       | 0xD000        |
| Entertainment Module | 0xD200        |
| DND Module           | 0xD400        |

**How to start with esp_32_vendor:**

1. Create a directory name 'esp' and clone this project in it.
2. run source esp_32_vendor/scripts/envsetup.sh
3. lunch (choose the target)
4. flash_target
5. monitor_target (choose the device which you want to monitor).

**How to create new target:**

1. Create a new csv file inside esp_32_vendor/targets/.
2. Follow the template from other target file.
3. Mention the project name and path in required order.

**How to override projects from esp-idf/examples:**

1. In esp_32_vendor/examples, create the same path as followed in esp-idf/examples for the project.
2. Customize it as per the requirement.
3. Now while building and flashing, It will search for the project in esp_32_vendor/examples. If not found then it will look into esp-idf/examples.

**Command used to flash the csv target in multiple esp_32 nodes**

```sh
flash_target
```

**Command used to monitor the csv target for multiple esp_32 nodes**

```sh
monitor_target
```
