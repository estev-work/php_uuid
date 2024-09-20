Certainly! Below is a comprehensive `README.md` file for your PHP UUID extension project, written in both **Russian** and **English**. This README includes sections such as project description, features, installation instructions, usage examples, testing procedures, and contribution guidelines.

---

# PHP UUID Extension

## Table of Contents

1. [Описание проекта](#описание-проекта)
2. [Особенности](#особенности)
3. [Установка](#установка)
4. [Использование](#использование)
5. [Тестирование](#тестирование)
6. [Вклад в проект](#вклад-в-проект)
7. [Лицензия](#лицензия)
8. [Project Description](#project-description)
9. [Features](#features)
10. [Installation](#installation)
11. [Usage](#usage)
12. [Testing](#testing)
13. [Contributing](#contributing)
14. [License](#license)

---

## Описание проекта

PHP расширение для генерации UUID (Universally Unique Identifier) различных версий: 1, 2, 3, 4, 5, 7 и Nil. Расширение написано на языке C и предназначено для использования в PHP 8.3 и более ранних версиях.

## Особенности

- **Поддерживаемые версии UUID:**
    - **v1**: Временная версия
    - **v2**: Версия DCE Security (не реализована)
    - **v3**: Именная версия на основе MD5
    - **v4**: Случайная версия
    - **v5**: Именная версия на основе SHA-1
    - **v7**: Временная упорядоченная версия
    - **Nil**: Нулевая UUID

- **Производительность**: Быстрая генерация UUID благодаря реализации на C.
- **Совместимость**: Работает с PHP 8.3 и более ранними версиями.
- **Тестирование**: Включены C-основанные тесты для проверки корректности генерации UUID.

## Установка

### Требования

- PHP 8.3 или выше (также совместимо с более ранними версиями)
- Компилятор C (например, `gcc`)
- Autotools (`autoconf`, `automake`, `libtool`)
- OpenSSL (для генерации хешей в UUID v3 и v5)

### Шаги установки

1. **Клонируйте репозиторий:**

    ```bash
    git clone https://github.com/yourusername/php-uuid-extension.git
    cd php-uuid-extension
    ```

2. **Соберите и установите расширение:**

    ```bash
    phpize
    ./configure --enable-uuid
    make
    sudo make install
    ```

3. **Включите расширение в `php.ini`:**

   Добавьте следующую строку в ваш `php.ini`:

    ```ini
    extension=uuid.so
    ```

4. **Проверьте установку:**

   Выполните команду `php -m | grep uuid`. Если расширение установлено правильно, вы увидите `uuid` в списке модулей.

## Использование

После установки расширения вы можете использовать функции генерации UUID в своих PHP-скриптах.

### Пример `index.php`

```php
<?php
echo "UUID v1: " . generate_uuid_v1() . PHP_EOL;
echo "UUID v2: " . generate_uuid_v2() . PHP_EOL;
echo "UUID v3: " . generate_uuid_v3("6ba7b810-9dad-11d1-80b4-00c04fd430c8", "example") . PHP_EOL;
echo "UUID v4: " . generate_uuid_v4() . PHP_EOL;
echo "UUID v5: " . generate_uuid_v5("6ba7b810-9dad-11d1-80b4-00c04fd430c8", "example") . PHP_EOL;
echo "UUID v7: " . generate_uuid_v7() . PHP_EOL;
echo "UUID Nil: " . generate_uuid_nil() . PHP_EOL;
?>
```

### Вывод

```
UUID v1: e4eaaaf2-7cd6-11ec-80d2-000c293e5c7f
UUID v2: UUID v2 generation not implemented
UUID v3: 3d813cbb-47fb-32ba-91df-831e1593ac29
UUID v4: f47ac10b-58cc-4372-a567-0e02b2c3d479
UUID v5: 21f7f8de-8051-5b89-8680-0195ef798b6a
UUID v7: 0187f6b5-05c0-7e80-9a4e-2bafc0c90269
UUID Nil: 00000000-0000-0000-0000-000000000000
```

## Тестирование

Проект включает C-основанные тесты для проверки всех функций генерации UUID.

### Сборка и запуск тестов

1. **Перейдите в каталог тестов:**

    ```bash
    cd tests
    ```

2. **Сделайте скрипт тестов исполняемым:**

    ```bash
    chmod +x run_tests.sh
    ```

3. **Запустите тесты:**

    ```bash
    ./run_tests.sh
    ```

### Ожидаемый вывод

```
Running UUID Generation Tests...

generate_uuid_v1: PASS
generate_uuid_v2: PASS
generate_uuid_v3: PASS
generate_uuid_v4: PASS
generate_uuid_v5: PASS
generate_uuid_v7: PASS
generate_uuid_nil: PASS

All tests completed.
```

### Использование Valgrind для проверки утечек памяти (опционально)

```bash
valgrind --leak-check=full ./test_uuid
```