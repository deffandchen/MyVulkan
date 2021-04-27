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
	GLFWwindow* window;   //��ʾ����

	VkInstance instance;   //vulkanʵ��

	void initWindow() {
		glfwInit();  //�����ʼ��

		//���ô���ѡ��  ��һ��������ѡ������֣��ڶ���������ѡ���ֵ
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  //���ڲ��ɵ�

		//��������
		window = glfwCreateWindow(WIDTH, HEIGHT,title,nullptr,nullptr);

	}

	void initVulkan() {
		createInstance();
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {  //��鴰���Ƿ���Ҫ�ر�
			glfwPollEvents();   //����Ƿ����¼�������
		}
	}

	//����ʵ�����ʹ���
	void cleanUp() {
		vkDestroyInstance(instance,nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}

	//����vulkanʵ��
	//ͨ��appInfo��createInfo�����ṹ�嶨��vulkanʵ���Ĳ���
	//vulkan�д�����Ϣ��ͨ���ṹ�嶨��
	void createInstance() {
		VkApplicationInfo appInfo = {}; //�ṹ���ʼ��
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

		//����ʵ��
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
