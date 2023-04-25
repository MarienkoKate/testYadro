# Тестовое задание
## Запуск программы Linux
Склонировать репозиторий

```
git clone https://github.com/MarienkoKate/testYadro.git
```
Перейти в директорию

```
cd testYadro
```
Скомпилировать файлы

```
g++ -o main Main.cpp Cafe.cpp
```

Запуск

```
./main file1
```

## Тесты



`file1` - Случай, когда время события меньше времени предыдущего события

`file2` - Случай, когда номер стола, который хочет занять клиент больше общего числа столов

`file3` - Тестовый файл из задания

![Image alt](https://github.com/MarienkoKate/testYadro/blob/main/results/3.png)

`file4` - Случаи, когда:

- клиент уже есть в клубе и пытается зайти снова;

- в очереди ожидания клиентов больше, чем общее число столов;

- клиент не находится в компьютерном клубе, но пытается занять стол.

![Image alt](https://github.com/MarienkoKate/testYadro/blob/main/results/4.png)

Демонстрация работы столов:
```
1 стол:

09:54 - 12:33 client1
12:33 - 15:52 client4
15:52 - 19:00 client6
```
```
2 стол:

10:25 - 12:43 client2
12:43 - 19:00 client5
```
```
3 стол:

10:59 - 19:00 client3

```



`file5` - Случаи, когда:

- клиент пришел раньше открытия клуба;

- клиент уже есть в клубе и пытается зайти снова;

- из компьютерного клуба пытается уйти клиент, который в нем не находится;

- клиент пытается снова сесть за свой же стол;

![Image alt](https://github.com/MarienkoKate/testYadro/blob/main/results/5.png)

Демонстрация работы столов:
```
1 стол:

09:54 - 11:36 client1
```
```
2 стол:

10:25 - 12:43 client2
```
```
3 стол:

10:59 - 19:00 client3

```
```
4 стол:

11:36 - 12:30 client1
12:30 - 15:52 client4
```



