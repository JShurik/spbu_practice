# Код задач с курса "Практикум на ЭВМ"
СПбГУ, 2021 год поступления


## 1 семестр
### Задачи математические
1. Алгоритм Евклида 
    - классичсекий
    - рекурсивный
    - бинарный
2. Возведение числа в степень по модулю
    - Рекурсивно
    - Алгоритм, основанный на повторном возведении в квадрат числа x
    - ~~Задание со звездочкой: нахождение n-ого числа Фибоначчи~~ (не реализовано)
3. Расширенный евклид
    - Сам расширенный алгоритм
    - Нахождение обратного в кольце остатков
4. Решение линейных диофантовых уравнений
    - ~~Задание со звездочкой: о разрешимости диофантового уравнения в натуральных коэффициэнтах~~ (не реализовано)
5. Китайская теорема об остатках
    - 2 способа реализации
    - Задание со звездочкой: найти общее решение для случаев, когда модули не взаимно простые
6. Символ Лежандра
    - с помощью критерия Эйлера и Задачи 2
    - с помощью Квадратичного закона взаимности и эвклидова деления
        - Сравнить скорость двух алгоритмов
7. Решение квадратичного сравнения
### Реализация структуры big_int
8. Основные конструирующие функции
    - Чтение и запись числа в структуру
    - Печать числа в консоль
    - malloc, calloc, free, assign
9. Сложение в big_int
10. Вычитаниие в big_int
11. Сдвиг влево и умножение
12. Деление с остатком (одна и та же функция должна возвращать и неполное частное, и остаток)
13. Аналог Задачи 2 - big_int_mod_pow

## 2 семестр
### Различные структуры
1. Полиномы в виде линейных списков
    - Парсер
    - Арифметика (сложение и умножение полиномов)
2. Реализовать калькулятор обратной польской записи посредством стека (с функциями НОД и НОК)
3. Перевод арифметического выражения из инфиксной записи в постфиксную с помощью стека
4. Бинарное дерево поиска
    - Обыкновенная древесная сортировка
    - Дерево Штерна-Броко
### Задачи на графах
5. Граф в виде списка смежности (построение графа)
    - Введение элементарных функций работы с графом
6. Проверка на двудольность
    - Обходом в широну
    - Обходом в глубину
7. Топологическая сортировка
8. Функции для записи графа в файл и чтения из него
9. Компоненты сильной связности I
    - "Классический" алгоритм с двумя проходами DFS и транспонированием графа
10. Компоненты сильной связности II
    - Альтернативный алгоритм. Основан на том, что мы отслеживаем по ходу DFS те моменты времени, в которые можно вернуться. Что-то похожее на этот алгоритм носит название Tarjan's SCC algorithm.
11. 2-CNF-SAT
#### Конечные автоматы
12. Детерминированный Конечный Автомат 
13. Операции над ДКА
    - Дополнение
    - Пересечение
    - Объединение
    - Разность
14. ДКА-калькулятор
15. ~~Дополнить работу с автоматами интерпретатором для несложных команд~~ (не реализовано)
16. ~~Описание ДКА в виде логических формул~~ (не реализовано)


