
const sf::VideoMode _1920x1080(1920,1080);
const sf::VideoMode _1776x1000(1776, 1000);
const sf::VideoMode _1680x1050(1680, 1050);
const sf::VideoMode _1600x1200(1600, 1200);
const sf::VideoMode _1600x900(1600, 900);
const sf::VideoMode _1440x900(1440, 900);
const sf::VideoMode _1366x768(1366, 768);
const sf::VideoMode _1360x1024(1360, 1024);
const sf::VideoMode _1360x768(1360, 768);
const sf::VideoMode _1280x1024(1280, 1024);
const sf::VideoMode _1280x960(1280, 960);
const sf::VideoMode _1280x800(1280, 800);
const sf::VideoMode _1280x768(1280, 768);
const sf::VideoMode _1280x720(1280, 720);
const sf::VideoMode _1152x864(1152, 864);
const sf::VideoMode _1152x648(1152, 648);
const sf::VideoMode _1024x768(1024, 768);
const sf::VideoMode _800x600(800, 600);
const sf::VideoMode _600x480(600, 480);

#define BUTTON_A sf::Joystick::X // A button on controller
#define BUTTON_X sf::Joystick::Z // X button on controller
#define BUTTON_B sf::Joystick::Y // B button on controller
#define BUTTON_Y sf::Joystick::R // Y button on controller
#define BUTTON_LB sf::Joystick::U // Left bumper on controller
#define BUTTON_RB sf::Joystick::V // Right bumper on controller
#define AXIS_LEFT_X sf::Joystick::Axis::X //  Left stick x value
#define AXIS_LEFT_Y sf::Joystick::Axis::Y // Left stick y value
#define AXIS_RIGHT_X sf::Joystick::Axis::U // Right stick x value
#define AXIS_RIGHT_Y sf::Joystick::Axis::R // Right stick y value
#define TRIGGERS sf::Joystick::Axis::Z // Positive Z = LT, and Negative Z = RT
#define BUTTON_BACK sf::Joystick::PovX // Back button on controller
#define BUTTON_START sf::Joystick::PovY // Start button on controller
#define DPAD_X sf::Joystick::Axis::PovX // Dpad left and right
#define DPAD_Y sf::Joystick::Axis::PovY // Dpad Up and down