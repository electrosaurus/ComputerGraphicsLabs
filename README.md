# Лабораторные работы по курсу компьютерной графики

Каждой лабораторной работе соответствует программа, считывающая данные из текстовых файлов
и выводящая результаты в виде GIF-изображений.

Файлы с входными данными помещаются в директории `input/lab*/`;
результаты работы программ выводятся в соответствующие директории `output/lab*/`.

## Установка
``` shell
# Клонируем репозиторий
git clone https://github.com/electrosaurus/ComputerGraphicsLabs.git
# Заходим в директорию
cd ComputerGraphicsLabs
# Собираем все лабораторные работы
make
```

*Для сборки конкретной лабораторной работы можно использовать `make lab1`, `make lab2` и т.д.*

## Лабораторная работа 1

### Реализованные функции

1. Отрисовка отрезка;
2. Отрисовка контура полигона;
3. Закраска полигона по правилу EO;
4. Закраска полигона по провилу NZW.

### Файлы с входными данными

* #### Параметры отрезка
  * Первая строка — размеры области вывода;
  * Вторая и третья строки — координаты начала и конца отрезка.

  Пример:
  ```
  200 200
  10 100
  150 150
  ```

* #### Параметры полигона
  * Первая строка — размеры области вывода;
  * Последующие строки — координаты вершин.

  Пример (пятиконечная звезда):
  ```
  200 200
  10 10
  100 190
  190 10
  10 130
  190 130
  ```

### Запуск программы

Программа принимает два аргумента:
1. Путь к файлу с параметрами отрезка;
2. Путь к файлу с параметрами полигона.

Пример запуска:

``` shell
bin/lab1 input/lab1/segment.txt input/lab1/star_polygon.txt
```

### Вывод программы

Программа выводит 4 GIF-изображения:
1. `output/lab1/segment.gif` — отрезок;
2. `output/lab1/polygon.gif` — контур полигона;
3. `output/lab1/polygon_fill_eo.gif` — полигон, закрашенный по правилу EO;
4. `output/lab1/polygon_fill_nzw.gif` — полигон, закрашенный по правилу NZW.

## Лабораторная работа 2

Реализованные функции:
1. Вывод кубической кривой Безье;
2. Отсечение отрезка прямоугольником (использован алгоритм *Cohen–Sutherland*).

### Файлы с входными данными

* #### Параметры кубической кривой Безье
  * Первая строка — размеры области вывода;
  * Последующие строки — координаты опорных точек.
  
  Пример:
  ```
  200 200
  80 10
  180 100
  150 100
  70 180
  ```

* #### Параметры отрезка и прямоугольника-отсекателя
  * Первая строка — размеры области вывода;
  * Вторая и третья строка — координаты начала и конца отрезка;
  * Четвертая и пятая строка — координаты нижней левой и верхней правой вершин прямоугольника-отсекателя.

  Пример:
  ```
  200 200
  60 10
  160 180
  50 60
  140 190
  ```

### Запуск программы

Программа принимает два аргумента:
1. Путь к файлу с параметрами кривой Безье третьего порядка;
2. Путь к файлу с параметрами отрезка и прямоугольника-отсекателя.

Пример запуска:

``` shell
bin/lab2 input/lab2/bezier_curve_3.txt input/lab2/segment_clipping.txt
```

### Вывод программы

Программа выводит 2 GIF-изображения:
1. `output/lab2/bezier_curve_3.gif` — кривая Безье третьего порядка;
2. `output/lab2/segment_clipping.gif` — анимация отсечения отрезка прямоугольником.


