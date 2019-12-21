#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>



int     cat(int, int);
void printHelp();
void printVersion();
void printError(int);



int main(int argc, char *argv[])
{
        // Стандартный поток ввода.
        int in = STDIN_FILENO;
        // Стандартный поток вывода.
        int const out = STDOUT_FILENO;

        // Ключ.
        int c;
    int ind = 0;

    // Ключи.
        static struct option options[] =
        {
                {"help",    0, NULL, 'h'},
                {"version", 0, NULL, 'v'},
                {NULL,      0, NULL,  0 },
    };

    // Чтение строки ключей.
    c = getopt_long(argc, argv, "hv", options, &ind);

        // Обработка ключей.
        switch(c)
    {
                case 'h': case '?':
            printHelp();

                case 'v':
            printVersion();
    }

        (void)argc;
        (void)*argv++;

        do
        {
                // Если есть аргументы.
                if (*argv != NULL)
                {
                        // Стандартный поток ввода.
                if (*argv[0] == '-' && *argv[1] == '\0')
                                in = STDIN_FILENO;
                        else
                        {
                                // Открытие файла.
                                in = open(*argv, O_RDONLY);

                                // Ошибка.
                                if (in == -1)
                                        printError(-1);
                        }

                        (void)*argv++;
                }

                // Ошибка.
                if (cat(in, out) == -1)
                        printError(-2);

                // Ошибка.
                if (in != STDIN_FILENO && close(in) == -1)
                        printError(-3);
        } while (*argv);

        return 0;
}


// Функция cat.
int cat(int in, int const out)
{
        ssize_t r, offset, w = 0;
        static char buffer[256];

        // Чтение данных из файла в буфер.
        while ((r = read(in, buffer, sizeof buffer)) != -1 && r != 0)
        {
                for (offset = 0; r; r -= w, offset += w)
                {
                        // Запись данных из буфера в файл.
                        w = write(out, buffer + offset, (size_t)r);

                        if (w == 0 || w == -1)
                                printError(-3);
                }
        };

        if (r < 0)
                printError(-2);

        return 0;
}


// Обработка ошибок.
void printError(int errno)
{
        switch (errno)
        {
                case -1:
                        write
                        (STDOUT_FILENO,
                        "Ошибка открытия файла!\n",
                        sizeof "Ошибка открытия файла!\n" - 1
                        );
                        break;
                case -2:
                        write
                        (1,
                        "Ошибка чтения файла!\n",
                        sizeof "Ошибка чтения файла!\n" - 1
                        );
                        break;
                case -3:
                        write
                        (1,
                        "Ошибка записи в файл!\n",
                        sizeof "Ошибка записи в файл!\n" - 1
                        );
                        break;
                case -4:
                        write
                        (1,
                        "Ошибка ввода/вывода в консоль!\n",
                        sizeof "Ошибка ввода/вывода в консоль!\n" - 1
                        );
                default:
                        write
                        (1,
                        "Ошибка!\n",
                        sizeof "Ошибка!\n" - 1
                        );
        }

        _exit(-1);
}


// Ключ "помощь".
void printHelp()
{
        int errno =
    write
        (STDOUT_FILENO,
    "\n./mycat - объединяет файлы и выводит их на стандартный вывод\n"
    "Использование:\n"
    "./mycat [OPTION]... [FILE]...\n\n"
    "Доступные опции:\n"
    "\t    --help\n"
    "\t\tвыводит справку\n"
    "\t    --version\n"
    "\t\tвыводит информацию о версии программы\n\n"
    "Если FILE не задан или задан как -, то читает стандартный ввод\n",
        sizeof
        "\n./cat - объединяет файлы и выводит их на стандартный вывод\n"
    "Использование:\n"
    "./cat [OPTION]... [FILE]...\n\n"
    "Доступные опции:\n"
    "\t    --help\n"
    "\t\tвыводит справку\n"
    "\t    --version\n"
    "\t\tвыводит информацию о версии программы\n\n"
    "Если FILE не задан или задан как -, то читает стандартный ввод\n" - 1
        );

        if (errno <= 0)
                printError(-4);
        else
                _exit(0);
}


// Ключ "версия".
void printVersion()
{
    int errno =
        write
        (1,
    "\nmycat 1.0\nАналог программы cat, созданный для учебных целей.\n",
    sizeof "\nmycat 1.0\nАналог программы cat, созданный для учебных целей.\n" - 1
    );

        if (errno <= 0)
                printError(-4);
        else
                _exit(0);
}
