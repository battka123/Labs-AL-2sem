// Copyright 2023 Ivan <i.suschin@yandex.ru>

#include "substring.hpp"

/* Наивный поиск подстроки в строке

 Подходит для маленьких подстрок и очень прост.
 Сравнивает символ подстроки и строки, неподходит — идёт дальше.

 Cложность: O(mn)
*/
size_t str_find(const std::string& str, const std::string& substr) {
  if (!str.empty()) {
    for (size_t m = 0; m != str.size(); ++m) {
      for (size_t n = 0; n != substr.size(); ++n) {
        if (str[m + n] != substr[n]) {
          break;
        }
        if (n == substr.size() - 1) return m;
      }
    }
  } else {
    return 0;
  }
  return -1;
}
/*
 Поиск Рабина-Карпа

 Используется полиномиальный хеш. Считаем хэш подстроки длины n, потом
 сравниваем с хэшом строки [0;n-1], сдвигаем правее и также сравниваем.
 Если хэш совпадает, сравниваем символы подстроки и данной части строки.
 Недостаток: может быть большой хэш.
 Плюсс в том, что алгорим имеет хорошее быстродействе.

 Сложность: О(n) в среднем, O(mn) в худшем случае.
*/
size_t rk_find(const std::string& str, const std::string& substr) {
  const int t = 256;
  const int w = 1283;
  // Длина строки str.
  int tlen = str.length();

  // Длина строки substr.
  int plen = substr.length();

  int flag;
  int c = 1, i = 0;

  // Считает hash_p(хэш-значение substr) и hash_0
  int hash_p = 0, hash = 0;
  while (i < plen) {
    hash_p = (hash_p * t + substr[i]) % w;
    hash = (hash * t + str[i]) % w;
    i++;
  }

  // Считает (t^(plen-1))%w
  for (int j = 1; j <= plen - 1; ++j) c = (c * t) % w;

  i = 0;
  while (i <= tlen - plen) {
    if (hash_p == hash) {
      flag = 1;
      for (int j = 0; j < plen; j++) {
        if (substr[j] == str[i + j]) {
          continue;
        } else {
          flag = 0;
          break;
        }
      }
      if (flag == 1) return i;
    }

    // Вычислю хэш-значение следующего окна
    // hash_i+1 = t * {hash_i - str[i] * t^(plen-1)} + str[i+plen]
    if (i < tlen - plen) {
      hash = ((t * (hash - str[i] * c)) + str[i + plen]) % w;
      if (hash < 0) {
        hash = hash + w;
      }
    }
    i++;
  }
  return -1;
}
/* Алгоритм Кнута—Морриса—Пратта
 Имеет сложность времени O(n), а сложность по памяти O(m).
 Похож на наивный алгоритм, но при несовпадении использует функцию LPS
 */
void lps_func(const std::string& substr, std::vector<int>& Lps) {
  Lps[0] = 0;
  int len = 0;
  size_t i = 1;
  while (i < substr.length()) {
    if (substr[i] == substr[len]) {
      len++;
      Lps[i] = len;
      i++;
      continue;
    } else {
      if (len == 0) {
        Lps[i] = 0;
        i++;
        continue;
      } else {
        len = Lps[len - 1];
        continue;
      }
    }
  }
}
size_t kmp_find(const std::string& str, const std::string& substr) {
  if (!substr.empty()) {
    int n = str.length();
    int m = substr.length();
    std::vector<int> Lps(m);

    lps_func(substr, Lps);  // Функция для заполнения вектора.

    int i = 0, j = 0;
    while (i < n) {
      if (substr[j] == str[i]) {
        i++;
        j++;
      }  // При совпадении продолжаем.

      if (j == m) {
        return (i - m);
        // При j==m мы нашли подстроку
        // выводим индекс
        // обновляем последний совпадающий символ

      } else if (i < n && substr[j] != str[i]) {  // При несовпадении
        if (j == 0)
          i++;
        else
          j = Lps[j - 1];  // обновляем последний совпадающий символ
      }
    }
  } else {
    return 0;
  }
  return -1;
}
