#include "Scene.h"

class Title : public Scene {
public:
    int ENEMY_COUNT = 1;
    
    ~Title();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
