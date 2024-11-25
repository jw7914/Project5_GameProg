#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 8

constexpr char ENEMY_FILEPATH[]       = "enemy2.png";

unsigned int LEVELB_DATA[] =
{
    136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 138,
    136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 138,
    136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 138,
    136, 0, 118, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 136,
    136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 138,
    136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 138,
    138, 119, 119, 119, 119, 119, 119, 119, 119, 139, 0, 0, 0, 138,
    136, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0, 0, 138
};

LevelB::~LevelB()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelB::initialise()
{
    m_game_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("new_tilemap.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, map_texture_id, 1.0f, 20, 9);
    
    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    // Existing
    
    std::vector<GLuint> cat_texture_ids = {
        Utility::load_texture("Meow-Knight_Idle.png"),   // IDLE spritesheet
        Utility::load_texture("Meow-Knight_Attack_3.png"),  // ATTACK spritesheet
        Utility::load_texture("Meow-Knight_Death.png"), // DEATH spritesheet
        Utility::load_texture("Meow-Knight_Dodge.png"), // RUN spritesheet
        Utility::load_texture("Meow-Knight_Take_Damage.png") // DAMAGE spritesheet
    };

    std::vector<std::vector<int>> cat_animations = {
        {0, 1, 2, 3, 4, 5},       // IDLE animation frames
        {0, 1, 2, 3},  // ATTACK animation frames
        {0, 1, 2, 3, 4, 5},       // DEATH animation frames
        {2, 2, 3, 3, 5, 5, 6, 6}, //RUN animation frames
        {0, 1, 2} //DAMAGE animation frames
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);
        
    m_game_state.player =  new Entity(
                                      cat_texture_ids,
                                      5.0f,
                                      acceleration,
                                      3.0f,
                                      cat_animations,
                                      0.0f,
                                      3,
                                      0,
                                      1,
                                      3,
                                      0.75f,
                                      1.0f,
                                      PLAYER,
                                      DEFAULT
                                  );
        
    m_game_state.player->set_position(glm::vec3(11.0f, 0.0f, 0.0f));

    // Jumping
    m_game_state.player->set_jumping_power(3.0f);
    
    /**
    Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] =  Entity(enemy_texture_id, 0.0f, 0.75f, 1.0f, ENEMY, JUMPING);
        m_game_state.enemies[i].set_scale(glm::vec3(1.0f,1.0f,0.0f));
        m_game_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
        m_game_state.enemies[i].activate();
        m_game_state.enemies[i].set_entity_type(ENEMY);
        m_game_state.enemies[i].set_speed(1.0f);
        m_game_state.enemies[i].set_ai_type(JUMPING);
        m_game_state.enemies[i].set_position(glm::vec3(1.0f, -5.0f, 0.0f));
    }
    
    
    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_game_state.bgm = Mix_LoadMUS("dooblydoo.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2.0);
    
    m_game_state.jump_sfx = Mix_LoadWAV("bounce.wav");
    
}

void LevelB::update(float delta_time)
{
    int playerCollsion = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    std::cout << "Player X: " << m_game_state.player->get_position().x << std::endl;
    std::cout << "Player Y: " << m_game_state.player->get_position().y << std::endl;

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, 0, m_game_state.map);
    }
    
//    if (m_game_state.player->get_position().y < -10.0f) m_game_state.next_scene_id = 1;

}

void LevelB::render(ShaderProgram *program)
{
    m_game_state.map->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        if (m_game_state.enemies[i].isActive()){
            m_game_state.enemies[i].render(program);
        }
    }
    m_game_state.player->render(program);
}


