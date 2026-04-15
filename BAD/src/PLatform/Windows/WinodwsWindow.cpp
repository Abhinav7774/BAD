#include "badpch.h"
#include "WindowsWindow.h"
#include "BAD/Event/ApplicationEvent.h"
#include "BAD/Event/KeyEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern float s_PlayerVelocity;

namespace BAD {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		BAD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	static unsigned int s_Shader;
	static unsigned int s_VAO;

	
	static float s_PlayerY = 0.0f;


	static float s_PipeX[3] = { 0.5f, 1.2f, 1.9f };
	static float s_PipeOffsetY[3] = { 0.0f, 0.3f, -0.2f };

	static float s_Gap = 0.4f;
	static bool s_GameOver = false;
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}



	void WindowsWindow::OnUpdate() const {

		float gravity = -0.0045f;

		if (!s_GameOver)
		{
		    float s_Velocity = s_PlayerVelocity;
			s_PlayerVelocity = 0.0f;
			s_Velocity += gravity;
			s_PlayerY += s_Velocity;

			if (s_PlayerY > 0.9f) { s_PlayerY = 0.9f; }
			if (s_PlayerY < -0.9f) { s_PlayerY = -0.9f; }

			for (int i = 0; i < 3; i++)
			{
				s_PipeX[i] -= 0.005f;
				if (s_PipeX[i] < -1.2f)
					s_PipeX[i] = 1.2f;
			}
		}

		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(s_Shader);
		glBindVertexArray(s_VAO);

		auto draw = [&](float x, float y, float r, float g, float b)
			{
				int offsetLoc = glGetUniformLocation(s_Shader, "offset");
				int colorLoc = glGetUniformLocation(s_Shader, "color");

				glUniform2f(offsetLoc, x, y);
				glUniform3f(colorLoc, r, g, b);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			};

		float playerX = -0.7f;
		float size = 0.05f;

		
		draw(playerX, s_PlayerY, 0.2f, 0.8f, 1.0f);

		for (int i = 0; i < 3; i++)
		{
			float x = s_PipeX[i];
			float offsetY = s_PipeOffsetY[i];

			float topStart = offsetY + s_Gap;
			float bottomEnd = offsetY - s_Gap;

			for (float y = topStart; y < 1.0f; y += 0.1f)
				draw(x, y, 0.2f, 1.0f, 0.3f);

			for (float y = -1.0f; y < bottomEnd; y += 0.1f)
				draw(x, y, 0.2f, 1.0f, 0.3f);

			float pipeWidth = 0.1f;

			bool collideX = (playerX + size > x - pipeWidth) && (playerX - size < x + pipeWidth);
			bool collideTop = s_PlayerY + size > topStart;
			bool collideBottom = s_PlayerY - size < bottomEnd;

			if (collideX && (collideTop || collideBottom))
				s_GameOver = true;
		}

		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_data.title = props.m_title;
		m_data.height = props.m_height;
		m_data.width = props.m_width;

		BAD_CORE_DBUG("Creating Window {0} ({1}, {2})", m_data.title, m_data.width, m_data.height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			BAD_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

	
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(
			(int)m_data.width,
			(int)m_data.height,
			m_data.title.c_str(),
			nullptr,
			nullptr
		);

		BAD_CORE_ASSERT(m_window, "Window creation failed!");

		glfwMakeContextCurrent(m_window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BAD_CORE_ASSERT(status, "Failed to initialize GLAD!");

		glViewport(0, 0, m_data.width, m_data.height);

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowMoveEvent event(xpos, ypos);
			data.EventCallback(event);
		});


		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				glViewport(0, 0, width, height);

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});


		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyHoldEvent event(key,1);
					data.EventCallback(event);
					break;
				}
				}
			});

		const char* vertexSrc = R"(
		#version 410 core
		layout(location = 0) in vec2 aPos;
		uniform vec2 offset;
		void main() {
			gl_Position = vec4(aPos + offset, 0.0, 1.0);
		}
		)";

		const char* fragmentSrc = R"(
		#version 410 core
		out vec4 FragColor;
		uniform vec3 color;
		void main() {
			FragColor = vec4(color, 1.0);
		}
		)";

		auto compileShader = [](unsigned int type, const char* src) {
			unsigned int id = glCreateShader(type);
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);
			return id;
			};

		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		s_Shader = glCreateProgram();
		glAttachShader(s_Shader, vs);
		glAttachShader(s_Shader, fs);
		glLinkProgram(s_Shader);

		glDeleteShader(vs);
		glDeleteShader(fs);

		
		float vertices[] = {
			-0.05f, -0.05f,
			 0.05f, -0.05f,
			 0.05f,  0.05f,
			-0.05f,  0.05f
		};

		unsigned int indices[] = { 0,1,2, 2,3,0 };

		unsigned int VBO, EBO;

		glGenVertexArrays(1, &s_VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(s_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled ? 1 : 0);
		m_data.vsync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_data.vsync;
	}

}