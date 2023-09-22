# Лабораторная работа 3

## Цель
Цель работы - получение навыков работы с шаблонами и реализация шаблона класса. Кроме этого студент должен **самостоятельно** научиться прорабатывать интерфейс класса и методов под выдвинутые тредования: соблюдать требования по константности методов, верной передачи аргументов (по значению, по ссылке, по константной ссылке).

После выполнения работы, студент должен знать что такое шаблоны, что такое инстанцирование и что такое специализация шаблонов.

После выполнения студент должен уметь реализовывать шаблоны классов любой сложности (в рамках пройденной программы), знать синкаксис языка С++ в части шаблонов.

Студент, претендующий на отличные знания, должен понимать и использовать средства `type_trails`.

## Теоретическая часть

### Шаблоны
Шабло́ны (англ. template) - средство языка программирования, предназначенное для разработки обобщённых алгоритмов, без привязки к некоторым параметрам, зачастую без привязки к типам данных.

Шаблоны позволяют определить универсальные конструкции (функции и/или классы), которые не зависят от определенного типа.

#### Пример
Чтобы без шаблонов реализовать функцию определения минимального элемента из двух аргументов необходимо реализовать эту функцию для каждого типа

```cpp
float min(float a, float b) { return a < b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }
double min(double a, double b) { return a < b ? a : b; }
/// ...
```

Используя шаблоны, можно реализовать функцию один раз:

```cpp
template <class T>
T min(T a, T b) {
  return (a < b) ? a : b;
}
```

Ключевое слово `template` означает, что далее идет шаблон функии (или класса, если указывается перед определением класса).

В треугольных скобках `<>` указываются аргументы шаблона. Так в примере выше указывается, что аргуметом шаблона фукнции будет некий тип `T`. У шаблонов может быть несколько аргументов, которые перечисляются через запятую `template <class T, class U, class V>`.

Кроме ключевого слова `class` можно использовать ключевое слово `typename`. В большинстве случаев нет никакой разницы в использовании этих двух ключевых слов. Кроме единственного случая. Об этом можно почитать [по ссылке](https://docs.microsoft.com/ru-ru/archive/blogs/slippman/why-c-supports-both-class-and-typename-for-type-parameters).

##### Замечание
Шаблоны классов и функций рекомендуется определять в заголовочных файлах, а не делить на заголовчный файл и файл с реализацией.

### Инстанцирование
Инстанцирование шаблона – это генерация кода функции или класса по шаблону для конкретных параметров.

Различают неявное инстанцирование, которое происходит при вызове функции или создании объекта класса, и явное инстанцирование с помощью резервированного слова `template`. Инстанцирование можно делать только в точке программы, где доступна реализация шаблона функции или методов шаблонного класса.

#### Явное инстанцирование шаблона функции
```cpp
template double min(double, double);
```

#### Пример неявного инстанцирования
```cpp
int main() {
  int a = 0;
  int b = 0;
  std::cin >> a >> b;

  std::cout << min(a, b);
}
```

Во время компиляции исходного кода компилятор встречает вызов функции `min`. Он определяет тип для которого необходима эта фукнция, в примере этот тип `int`. И компилятор генерирует код функции по шаблону для конкретного типа `int`. Этот процесс можно представить так, что компилятор написал новый заголовочный файл в который перенес шаблонную функцию, только везде вместо типа `T` подставил тип `int`.

#### Замечание
Представим следующий код
```cpp
int main() {
  int a = 0;
  float b = 0;
  std::cin >> a >> b;

  std::cout << min(a, b);
}
```

В шаблонную функции передаются два разных типа `int` и `float`. Но в шаблоне аргументы объявлены как одинаковые типы:

```cpp
T min(T a, T b);
```
Для какого именно типа должен инстанцировать функцию компилятор: для `int` или для `float`? Компилятор не может однозначно ответить на этот вопрос, поэтому он делает единственно правильную вещь. Компилятор прерывает процесс компиляции и сообщает об ошибке времени компиляции разработчику. Это спасает от множества ошибок.

В подобных случаях у разработчика есть два варианта:
* переписать код таким образом, что неоднозначности не будет
* явно указать компилятору какой тип использовать

```cpp
int main() {
  int a = 0;
  float b = 0;
  std::cin >> a >> b;

  std::cout << min<float>(a, b); // Явно указываем, использовать float
  std::cout << min<int>(a, b); // Явно указываем, использовать int
  std::cout << min<double>(a, b); // Явно указываем, использовать double
}
```

### Специализация шаблонов
Иногда есть необходимость использовать код для некоторого шаблонного аргумента, который не совпадает с основным кодом шаблона.

Например, мы хотим реализовать функцию поиска минимума из двух Си-строк.

Если использовать обычный код шаблона, то будут сравниваться значения указателей, а не значения строк:
```cpp
const char* min(const char* a, const char* b) {
  return (a < b) ? a : b;
}
```
Выше представлен **некорректный** код, который получит компилятор испоьзуя реализованный шаблон фукнции `min`.

Эту проблему призвана решать специализация шаблонов. С помощью нее можно определить реализацию шаблона функции для одного типа данных, которая будет отличаться от реализации шаблона функции для другого типа данных.

Ниже специализация шаблона для Си-строк.
```cpp
template <>
const char* min(const char* a, const char* b) {
  return (strcmp(a, b) < 0) ? a : b;
}
```

Специализация бывает полной и частичной. Подробнее можно прочитать в [статье](https://ravesli.com/urok-179-chastichnaya-spetsializatsiya-shablona/).

## Задание

Реализуйте шаблон класса `Matrix`, используя "сырые" указатели и динамическое выделение памяти.

STL контейнеры и алгоритмы исползовать не разрешается.

Интерфейс класса следует проработать самостоятельно, основываясь на модульных тестах [tests/matrix_unittests.cpp](tests/matrix_unittests.cpp).

## Рекомендации
1. Шаблон класса реализуйте в файле `matrix.hpp`
2. Не забывайте о модификаторе `const` у методов, которые не изменяют содержимое объекта класса
3. Воспользуйтесь [`type_trails`](https://ru.cppreference.com/w/cpp/header/type_traits) и [`static_assert`](https://en.cppreference.com/w/cpp/language/static_assert), чтобы ваш класс был определен только для арифметических типов.