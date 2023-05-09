#include "application.h"

GLfloat angle = 0.0f;

void drawCube(float xrf, float yrf, float zrf)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);

    glRotatef(xrf, 1.0f, 0.0f, 0.0f);
    glRotatef(yrf, 0.0f, 1.0f, 0.0f);
    glRotatef(zrf, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);

        // front
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);

        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);

        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);

        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // back
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);

        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);

        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);

        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        // front - back
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);

        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);

        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd();
}

#ifdef __linux__
    int getch()
    {
        struct termios oldattr, newattr;

        tcgetattr(STDIN_FILENO, &oldattr);

        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        int ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

        return ch;
    }
#endif

Application::Application()
{
    this->isExecute(true);

    this->init("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
}

Application::~Application()
{
    this->isExecute(false);

    this->clean();
}

bool Application::isExecute() const
{
    return this->m_isExecute;
}

void Application::isExecute(bool isExecute)
{
    this->m_isExecute = isExecute;
}

void Application::execute()
{
    const uint8_t FPS = 60;
    int32_t tickInterval = 1000 / FPS;

    uint32_t lastUpdateTime = SDL_GetTicks();
    int32_t deltaTime = 0;

    while (this->isExecute()) {
        uint32_t currentTime = SDL_GetTicks();
        deltaTime = int32_t(currentTime - lastUpdateTime);

        int32_t timeToSleep = tickInterval - deltaTime;
        if (timeToSleep > 0) {
            SDL_Delay(timeToSleep);
        }

        this->handle();
        this->update();
        this->render();

        lastUpdateTime = currentTime;
    }
}

void Application::init(const char *title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Engine init..." << std::endl;

        this->window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (this->window != NULL) {
            std::cout << "Window created!" << std::endl;

            this->glContext = SDL_GL_CreateContext(this->window);
            if (this->glContext != NULL) {
                std::cout << "OpenGL context created!" << std::endl;
                std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
                std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LEQUAL);

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClearDepth(1.0f);

                glViewport(0, 0, width, height);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(0.0f, 0.0f, -5.0f);

                SDL_GL_SetSwapInterval(0);
            } else {
                std::cout << SDL_GetError() << std::endl;

                this->isExecute(false);
            }
        } else {
            std::cout << SDL_GetError() << std::endl;

            this->isExecute(false);
        }
    } else {
        std::cout << SDL_GetError() << std::endl;

        this->isExecute(false);
    }
}

void Application::handle()
{
    SDL_Event event;

    do {
        switch (event.type) {
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        this->isExecute(false);
                        break;
                }
                break;
            case SDL_QUIT:
                this->isExecute(false);
                break;
        }
    } while (SDL_PollEvent(&event));
}

void Application::update()
{
    //
}

void Application::render()
{
    drawCube(angle + 0.5f, angle + 0.3f, 0.0f);
    angle += 0.7f;

    SDL_GL_SwapWindow(this->window);
}

void Application::clean()
{
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();

    std::cout << "Engine clean..." << std::endl;
}
