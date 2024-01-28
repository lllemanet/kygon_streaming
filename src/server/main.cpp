#include "Application.hpp"
#include "common/Utils.hpp"

int main(int argc, char* argv[]) {
    kygon::server::Application app{argc, argv};
    if (!app.init()) {
        qKCritical() << "Can't init server Application, closing";
        return -1;
    }

    return app.exec();
}
