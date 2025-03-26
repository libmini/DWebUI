#include <iostream>
#include <sstream>

#include "webui.hpp"

void cpp_function_string(webui::window::event *e)
{

	// JavaScript:
	// cpp_function_string('Hello', 'World`);

	std::string str_1 = e->get_string(); // Or e->get_string(0);
	std::string str_2 = e->get_string(1);

	std::cout << "cpp_function_string 1: " << str_1 << std::endl; // Hello
	std::cout << "cpp_function_string 2: " << str_2 << std::endl; // World
}

void cpp_function_integer(webui::window::event *e)
{

	// JavaScript:
	// cpp_function_integer(123, 456, 789);

	long long number_1 = e->get_int(); // Or e->get_int(0);
	long long number_2 = e->get_int(1);
	long long number_3 = e->get_int(2);

	std::cout << "cpp_function_integer 1: " << number_1 << std::endl; // 123
	std::cout << "cpp_function_integer 2: " << number_2 << std::endl; // 456
	std::cout << "cpp_function_integer 3: " << number_3 << std::endl; // 789
	e->return_string("I'm sorry");
}

void cpp_function_boolean(webui::window::event *e)
{

	// JavaScript:
	// cpp_function_boolean(true, false);

	bool status_1 = e->get_bool(); // Or e->get_bool(0);
	bool status_2 = e->get_bool(1);

	std::cout << "cpp_function_boolean 1: " << (status_1 ? "True" : "False") << std::endl;
	std::cout << "cpp_function_boolean 2: " << (status_2 ? "True" : "False") << std::endl;
}

void cpp_function_with_response(webui::window::event *e)
{

	// JavaScript:
	// cpp_function_with_response(number, 2).then(...)

	long long number = e->get_int(0);
	long long times = e->get_int(1);

	long long res = number * times;

	std::cout << "cpp_function_with_response: " << number << " * " << times << " = " << res << std::endl;

	// Send back the response to JavaScript
	e->return_int(res);
}

void my_function_exit(webui::window::event *e)
{
	// Close all opened windows
	webui::exit();
}

void events(webui::window::event *e)
{
	if (e->event_type == WEBUI_EVENT_CONNECTED)
		std::cout << "Connected." << std::endl;
	else if (e->event_type == WEBUI_EVENT_DISCONNECTED)
		std::cout << "Disconnected." << std::endl;
	else if (e->event_type == WEBUI_EVENT_MOUSE_CLICK)
		std::cout << "Click." << std::endl;
	else if (e->event_type == WEBUI_EVENT_NAVIGATION)
	{
		std::cout << "Navigation to: " << e->get_string() << std::endl;

		std::string url = e->get_string();
		std::cout << "Starting Navigation to: " << url << std::endl;
		e->get_window().navigate(url);
	}
}

void my_function_count(webui::window::event* e) {

	// Create a buffer to hold the response
	char response[64] = {0};

	// This is another way to create a buffer:
	//  std::string buffer;
	//  buffer.reserve(64);
	//  my_window.script(..., ..., &buffer[0], 64);

	// Run JavaScript
	if (!e->get_window().script("return GetCount();", 0, response, sizeof(response))) {

		if (!e->get_window().is_shown())
			std::cout << "Window closed." << std::endl;
		else
			std::cout << "JavaScript Error: " << response << std::endl;
		return;
	}

	// Get the count
	int count = std::stoi(response);

	// Increment
	count++;

	printf("Count: %d\n", count);

	// Generate a JavaScript
	std::stringstream js;
	js << "SetCount(" << count << ");";

	// Run JavaScript (Quick Way)
	e->get_window().run(js.str());
}

webui::window second_window;

// This method gets called every time the
// user clicks on "SwitchToSecondPage"
void switch_to_second_page(webui::window::event* e) {
	// Switch to `/second.html` in the same opened window.
	e->get_window().show("second.html");
}

// This method gets called every time the
// user clicks on "OpenNewWindow"
void show_second_window(webui::window::event* e) {
	// Show a new window, and navigate to `/second.html`
	// if the window is already opened, then switch in the same window
	second_window.show("second.html");
}

int main()
{

	// 第一个页面逻辑
	webui::window win;
	win.bind("", events);
	second_window.bind("", events);

	// Bind HTML elements with C++ functions
	win.bind("cpp_function_string", cpp_function_string);
	win.bind("cpp_function_integer", cpp_function_integer);
	win.bind("cpp_function_boolean", cpp_function_boolean);
	win.bind("cpp_function_with_response", cpp_function_with_response);
	win.bind("Exit", my_function_exit);

	// C++调用JS
	win.bind("my_function_count", my_function_count);

	// 第二个页面逻辑
	win.bind("switch_to_second_page", switch_to_second_page);
	win.bind("show_second_window", show_second_window);
	second_window.bind("Exit", my_function_exit);

	// 设置根目录并加载 HTML 文件
	win.set_root_folder("./");
	win.set_size(450, 1040);
	win.set_position(1476, 0);
	win.set_runtime(NodeJS);
	win.show("index.html");
	webui::wait();
	webui::clean();
	return 0;
}

// #ifdef _WIN32
// // Release build
// int WINAPI
//     wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
// 	return main();
// }
// #endif