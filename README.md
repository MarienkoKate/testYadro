# Тестовое задание
## Запуск программы
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
./main file.txt
```

## Тесты

`file` - Тестовый файл из задания



`file1` - Случай, когда время события меньше времени предыдущего события



`file2` - Случай, когда номер стола, который хочет занять клиент больше общего числа столов



`file4` - Проверка входных данных



`file5` - Случаи, когда:

- клиент пришел раньше открытия клуба;

- клиент уже есть в клубе и пытается зайти снова;

- из компьютерного клуба пытается уйти клиент, который в нем не находится;

- клиент пытается снова сесть за свой же стол;

Результат работы программы:
![Image alt](https://github.com/MarienkoKate/testYadro/blob/main/results/5.jpeg)

Демонстрация работы столов
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



