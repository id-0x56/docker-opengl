#include "main.h"

Application *application = nullptr;

int main(int argc, char *argv[])
{
    application = new Application();
    application->execute();

    delete application, application = nullptr;

    return 0;
}
