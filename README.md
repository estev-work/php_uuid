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

## Вклад в проект

Мы приветствуем вклад от сообщества! Если вы хотите внести изменения или улучшения, пожалуйста, следуйте следующим шагам:

1. **Форкните репозиторий.**
2. **Создайте новую ветку для ваших изменений:**

    ```bash
    git checkout -b feature/your-feature-name
    ```

3. **Внесите изменения и закоммитьте их:**

    ```bash
    git commit -m "Добавить новую функцию для генерации UUID"
    ```

4. **Отправьте изменения в ваш форк:**

    ```bash
    git push origin feature/your-feature-name
    ```

5. **Создайте Pull Request на оригинальный репозиторий.**

## Лицензия

Этот проект лицензирован под лицензией MIT. Подробности см. в файле [LICENSE](LICENSE).

---

## Project Description

A PHP extension for generating UUIDs (Universally Unique Identifiers) of various versions: 1, 2, 3, 4, 5, 7, and Nil. The extension is written in C and is designed for use with PHP 8.3 and earlier versions.

## Features

- **Supported UUID Versions:**
    - **v1**: Time-based
    - **v2**: DCE Security version (not implemented)
    - **v3**: Name-based using MD5
    - **v4**: Random
    - **v5**: Name-based using SHA-1
    - **v7**: Time-ordered
    - **Nil**: Nil UUID

- **Performance**: Fast UUID generation thanks to C implementation.
- **Compatibility**: Works with PHP 8.3 and earlier versions.
- **Testing**: Includes C-based tests to ensure the correctness of UUID generation.

## Installation

### Requirements

- PHP 8.3 or higher (also compatible with earlier versions)
- C Compiler (e.g., `gcc`)
- Autotools (`autoconf`, `automake`, `libtool`)
- OpenSSL (for hashing in UUID v3 and v5)

### Installation Steps

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/php-uuid-extension.git
    cd php-uuid-extension
    ```

2. **Build and install the extension:**

    ```bash
    phpize
    ./configure --enable-uuid
    make
    sudo make install
    ```

3. **Enable the extension in `php.ini`:**

   Add the following line to your `php.ini`:

    ```ini
    extension=uuid.so
    ```

4. **Verify the installation:**

   Run `php -m | grep uuid`. If the extension is installed correctly, you will see `uuid` listed among the modules.

## Usage

After installing the extension, you can use the UUID generation functions in your PHP scripts.

### Example `index.php`

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

### Output

```
UUID v1: e4eaaaf2-7cd6-11ec-80d2-000c293e5c7f
UUID v2: UUID v2 generation not implemented
UUID v3: 3d813cbb-47fb-32ba-91df-831e1593ac29
UUID v4: f47ac10b-58cc-4372-a567-0e02b2c3d479
UUID v5: 21f7f8de-8051-5b89-8680-0195ef798b6a
UUID v7: 0187f6b5-05c0-7e80-9a4e-2bafc0c90269
UUID Nil: 00000000-0000-0000-0000-000000000000
```

## Testing

The project includes C-based tests to verify all UUID generation functions.

### Building and Running Tests

1. **Navigate to the tests directory:**

    ```bash
    cd tests
    ```

2. **Make the test script executable:**

    ```bash
    chmod +x run_tests.sh
    ```

3. **Run the tests:**

    ```bash
    ./run_tests.sh
    ```

### Expected Output

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

### Using Valgrind to Check for Memory Leaks (Optional)

```bash
valgrind --leak-check=full ./test_uuid
```

## Contributing

We welcome contributions from the community! If you wish to make changes or improvements, please follow these steps:

1. **Fork the repository.**
2. **Create a new branch for your changes:**

    ```bash
    git checkout -b feature/your-feature-name
    ```

3. **Make your changes and commit them:**

    ```bash
    git commit -m "Add new UUID generation function"
    ```

4. **Push your changes to your fork:**

    ```bash
    git push origin feature/your-feature-name
    ```

5. **Create a Pull Request to the original repository.**

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

**Note:** Replace `https://github.com/yourusername/php-uuid-extension.git` with the actual URL of your Git repository.