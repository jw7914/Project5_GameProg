//#include "Level1.h"
//#include "Utility.h"
//#include "Entity.h"
//
//#define LEVEL_WIDTH 16
//#define LEVEL_HEIGHT 10
//
//constexpr char SPRITESHEET_FILEPATH[] = "george_0.png",
//           PLATFORM_FILEPATH[]    = "platformPack_tile027.png",
//           ENEMY_FILEPATH[]       = "enemy1.png";
//
//const std::vector<std::vector<int>> cat_animations = {
//       {0, 1, 2, 3, 4, 5},       // IDLE animation frames
//       {0, 1, 2, 3},  // ATTACK animation frames
//       {0, 1, 2, 3, 4, 5},       // DEATH animation frames
//       {2, 2, 3, 3, 5, 5, 6, 6}, //RUN animation frames
//       {0, 1, 2} //DAMAGE animation frames
//   };
//
////const std::vector<GLuint> cat_texture_ids = {
////    Utility::load_texture("Meow-Knight_Idle.png"),   // IDLE spritesheet
////    Utility::load_texture("Meow-Knight_Attack_3.png"),  // ATTACK spritesheet
////    Utility::load_texture("Meow-Knight_Death.png"), // DEATH spritesheet
////    Utility::load_texture("Meow-Knight_Dodge.png"), // RUN spritesheet
////    Utility::load_texture("Meow-Knight_Take_Damage.png") // DAMAGE spritesheet
////};
//
//unsigned int MAP_DATA[] =
//{
//        10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  // Row 0
//        10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,  // Row 1
//        10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,  // Row 2
//        10, 0, 0, 0, 0, 0, 156, 156, 156, 156, 0, 0, 0, 0, 0, 10,  // Row 3
//        10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,  // Row 4
//        10, 0, 6, 6, 6, 6, 0, 0, 0, 0, 16, 16, 16, 16, 0, 10,  // Row 5
//        10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,  // Row 6
//        10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,  // Row 7
//        10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10,  // Row 8
//        10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20  // Row 9
//};
//
//Level1::~Level1()
//{
//    delete [] m_game_state.enemies;
//    delete    m_game_state.player;
//    delete    m_game_state.map;
//    Mix_FreeChunk(m_game_state.jump_sfx);
//    Mix_FreeMusic(m_game_state.bgm);
//}
//
//void Level1::initialise()
//{
//    GLuint map_texture_id = Utility::load_texture("new_tilemap.png");
//    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, MAP_DATA, map_texture_id, 1.0f, 4, 1);
//    
//    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);
//
////    m_game_state.player = new Entity(
////                                     cat_texture_ids,
////                                     5.0f,
////                                     acceleration,
////                                     3.0f,
////                                     cat_animations,
////                                     0.0f,
////                                     3,
////                                     0,
////                                     1,
////                                     3,
////                                     0.75f,
////                                     1.0f,
////                                     PLAYER,
////                                     DEFAULT
////                                 );
//    
//    m_game_state.player->set_position(glm::vec3(5.0f, 0.0f, 0.0f));
//
//    // Jumping
//    m_game_state.player->set_jumping_power(3.0f);
//    
//    /**
//     Enemies' stuff */
//    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);
//
//    m_game_state.enemies = new Entity[ENEMY_COUNT];
//
//    for (int i = 0; i < ENEMY_COUNT; i++)
//    {
//        m_game_state.enemies[i] =  Entity(enemy_texture_id, 0.0f, 1.0f, 1.0f, ENEMY, PATROL);
//    }
//
//
//    m_game_state.enemies[0].set_position(glm::vec3(8.0f, 0.0f, 0.0f));
//    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
//    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
//
//    /**
//     BGM and SFX
//     */
//    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
//    
//    m_game_state.bgm = Mix_LoadMUS("assets/dooblydoo.mp3");
//    Mix_PlayMusic(m_game_state.bgm, -1);
//    Mix_VolumeMusic(0.0f);
//    
//    m_game_state.jump_sfx = Mix_LoadWAV("assets/bounce.wav");
//}
//
//void Level1::update(float delta_time)
//{
//    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
//    
//    for (int i = 0; i < ENEMY_COUNT; i++)
//    {
//        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, NULL, m_game_state.map);
//    }
//}
//
//
//void Level1::render(ShaderProgram *g_shader_program)
//{
//    m_game_state.map->render(g_shader_program);
//    m_game_state.player->render(g_shader_program);
//    for (int i = 0; i < m_number_of_enemies; i++)
//            m_game_state.enemies[i].render(g_shader_program);
//}
