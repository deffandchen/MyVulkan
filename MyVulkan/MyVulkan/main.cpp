#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#include<stdexcept>
#include<cstdlib>
#include<iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const char* title = "Vulkan";

class TriangleApp {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
	}

private:
	GLFWwindow* window;   //显示窗口

	VkInstance instance;   //vulkan实例

	void initWindow() {
		glfwInit();  //必须初始化

		//设置窗口选项  第一个参数是选项的名字，第二个参数是选项的值
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  //窗口不可调

		//创建窗口
		window = glfwCreateWindow(WIDTH, HEIGHT,title,nullptr,nullptr);

	}

	void initVulkan() {
		createInstance();
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {  //检查窗口是否需要关闭
			glfwPollEvents();   //检查是否有事件被触发
		}
	}

	//销毁实例化和窗口
	void cleanUp() {
		vkDestroyInstance(instance,nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}

	//创建vulkan实例
	//通过appInfo、createInfo两个结构体定义vulkan实例的参数
	//vulkan中大量信息都通过结构体定义
	void createInstance() {
		VkApplicationInfo appInfo = {}; //结构体初始化
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		//创建实例
		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to ctreate instance!");
		}
	}


};

int main() 
{
	TriangleApp app;
	app.run();
	return 0;
}
