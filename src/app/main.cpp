#include "UiApplication.hpp"
#include "common/Utils.hpp"

int main(int argc, char* argv[]) {
    kygon::client::UiApplication app(argc, argv);
    if (!app.init()) {
        kLog(Critical) << "Can't init UiApplication";
        return -1;
    }

    return app.exec();
}
