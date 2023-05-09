#ifndef APPLICATION_H
    #define APPLICATION_H

    #include <iostream>

    #include <SDL2/SDL.h>

    #include <GL/gl.h>
    #include <GL/glu.h>

    #ifdef __linux__
        #include <unistd.h>
        #include <termios.h>
    #else
        #include <conio.h>
    #endif

    class Application
    {
        public:
            Application();

            ~Application();

            bool isExecute() const;
            void isExecute(bool isExecute);

            void execute();

        private:
            bool m_isExecute;

            SDL_Window *window;

            SDL_GLContext glContext;

            void init(const char *title, int x, int y, int width, int height, bool fullscreen = true);

            void handle();

            void update();

            void render();

            void clean();
    };
#endif
