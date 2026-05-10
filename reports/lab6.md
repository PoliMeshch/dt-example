# Лабораторная работа №6. Простые CI-CD пайплайны

## Ход работы

### Этап 1. Базовые хуки в Git на стороне клиента

#### 1.1. Хуки Git: операции и этапы.
Хуки - это скрипты, которые Git автоматически запускает при определённых событиях.

Хуки, которые могут прервать операцию:
- **pre-commit** - перед созданием коммита, после ввода сообщения.
- **commit-msg** - после ввода сообщения, проверка формата.
- **pre-merge-commit** - перед созданием merge-коммита.
- **pre-push** - перед отправкой в удалённый репозиторий.

Хуки, которые не могут прервать операцию:
- **post-commit** - после создания коммита (логирование, уведомления).
- **post-merge** - после слияния.
- **post-checkout** - после переключения ветки.

Источник: документация Git (https://git-scm.com/docs/githooks).

#### 1.2. Хук pre-commit: запрет файлов
Создан хук, проверяющий добавляемые файлы на наличие запрещённых паттернов. 
Я выбрала запрет на файлы `.env`, токены доступа и приватные ключи: `.env`, `.token`, `.pem`, `id_rsa`.

Файл `.git/hooks/pre-commit`:

```bash
#!/bin/sh

# Получение списка всех добавленных в индекс файлов
files=$(git diff --cached --name-only --diff-filter=ACM)

# Если файлы не добавлены
[ -z "$files" ] && exit 0

for f in $files; do
  case "$f" in
    *.env|*.token|*.pem|*id_rsa*)
      echo ">>> Ошибка: файл '$f' не может быть добавлен в репозиторий"
      exit 1
      ;;
  esac
done

exit 0
```

Сделан исполняемым: `chmod +x .git/hooks/pre-commit`.

**Тестирование:**
```bash
$ git commit -m "Test env"
>>> Ошибка: файл '.env' не может быть добавлен в репозиторий
```

#### 1.3. Хук commit-msg: проверка сообщения коммита
Создан хук, проверяющий, что сообщение коммита не пустое и начинается с заглавной буквы.

Файл `.git/hooks/commit-msg`:
```bash
#!/bin/sh

# Чтение сообщения коммита
MSG=$(cat "$1")

# Проверка, что сообщение не пустое
if [ -z "$MSG" ]; then
  echo ">>> Ошибка: сообщение коммита не может быть пустым"
  exit 1
fi

# Проверка, что первая буква заглавная
FIRST_CHAR=$(echo "$MSG" | cut -c 1)
case "$FIRST_CHAR" in
  [A-Z]) ;;
  *)
    echo ">>> Ошибка: сообщение должно начинаться с заглавной буквы"
    exit 1
    ;;
esac

exit 0
```

Сделан исполняемым: `chmod +x .git/hooks/commit-msg`.

**Тестирование:**
```bash
$ git commit -m "test message"
>>> Ошибка: сообщение должно начинаться с заглавной буквы

$ git commit -m "Test message"
[lab6-report 07ac112] Test message
 1 file changed, 1 insertion(+)
 create mode 100644 test.txt
```


### Этап 2. Хуки Git на стороне сервера

#### 2.1. Конвертация Markdown в HTML
Для конвертации Markdown в HTML установлен Pandoc:

```bash
sudo apt install pandoc
```

#### 2.2. Создание копии репозитория и настройка remote
Создана локальная копия репозитория, добавлена как удалённый репозиторий `server`:

```bash
git clone dt-example dt-example-copy
git remote add server ../dt-example-copy
```

В копии разрешён push в текущую ветку:

```bash
git config receive.denyCurrentBranch updateInstead
```

#### 2.3. Настройка хука post-receive
В копии репозитория создан хук `.git/hooks/post-receive`:

```bash
#!/bin/sh

while read oldrev newrev refname; do
    if [ "$refname" = "refs/heads/lab6-report" ]; then
        cd "/home/darel/dt-example-copy"
        git checkout -f lab6-report
        pandoc -s reports/lab6.md -o reports/lab6.html --metadata title="Lab 6"
        echo ">>> HTML обновлён: reports/lab6.html"
    fi
done

exit 0
```

Сделан исполняемым: `chmod +x .git/hooks/post-receive`.

#### 2.4. Проверка работы
После пуша в `server` хук автоматически генерирует HTML-версию отчёта:

```bash
$ git push server lab6-report
...
>>> HTML обновлён: reports/lab6.html
```

Файл `reports/lab6.html` открыт в браузере - отображается корректно, обновляется при новых пушах.


darel@MAIBENBEN-PC MINGW64 ~
$ git clone dt-example dt-example-copy
Cloning into 'dt-example-copy'...
done.
Updating files: 100% (37/37), done.


darel@MAIBENBEN-PC MINGW64 ~/dt-example (lab6-report)
$ git remote -v
origin  git@github.com:PoliMeshch/dt-example.git (fetch)
origin  git@github.com:PoliMeshch/dt-example.git (push)
server  ../dt-example-copy (fetch)
server  ../dt-example-copy (push)


darel@MAIBENBEN-PC MINGW64 ~/dt-example (lab6-report)
$ git push server lab6-report
Everything up-to-date
