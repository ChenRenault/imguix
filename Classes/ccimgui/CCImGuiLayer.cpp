
#include <math.h>
#include <vector>
#include <algorithm>

#include "CCImGuiLayer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui_impl_cocos2dx.h"
#include "CCIMGUI.h"
#include "ImGuizmo/ImGuizmo.h"
#include "ImGuizmo/ImSequencer.h"
#include "ImGuizmo/ImCurveEdit.h"

USING_NS_CC;

void ImGuiLayer::createAndKeepOnTop()
{
	// delay call, once.
	auto director = Director::getInstance();
	director->getScheduler()->schedule([=](float dt) {
		std::string layerName = "ImGUILayer";
		auto order = INT_MAX;
		auto layer = ImGuiLayer::create();
		auto runningScene = Director::getInstance()->getRunningScene();
		if (runningScene && !runningScene->getChildByName(layerName))
		{
			runningScene->addChild(layer, INT_MAX, layerName);
		}

		auto e = Director::getInstance()->getEventDispatcher();
		auto detached = false;
		e->addCustomEventListener(Director::EVENT_BEFORE_SET_NEXT_SCENE, [&](EventCustom *) {
			layer = dynamic_cast<ImGuiLayer *>(Director::getInstance()->getRunningScene()->getChildByName(layerName));
			if (layer)
			{
				layer->retain();
				layer->removeFromParent();
				detached = true;
			}
		});
		e->addCustomEventListener(Director::EVENT_AFTER_SET_NEXT_SCENE, [&](EventCustom *) {
			if (layer && detached)
			{
				Director::getInstance()->getRunningScene()->addChild(layer, order, layerName);
				layer->release();
				detached = false;
			}
		});
	},
									   director, 0, 0, 0, false, "checkIMGUI");
}

// on "init" you need to initialize your instance
bool ImGuiLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	// init imgui
	setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));

	// events
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch *touch, Event *) -> bool {
		bool inImGuiWidgets = ImGui::IsAnyWindowHovered();

		return inImGuiWidgets;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void ImGuiLayer::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags)
{
	Layer::visit(renderer, parentTransform, parentFlags);
	_command.init(_globalZOrder);
	_command.func = CC_CALLBACK_0(ImGuiLayer::onDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void ImGuiLayer::onDraw()
{
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	getGLProgram()->use();

	// create frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplCocos2dx_NewFrame();
	ImGui::NewFrame();

	ImGuizmo::BeginFrame();

	// draw all gui
	CCIMGUI::getInstance()->updateImGUI();

	// rendering
	glUseProgram(0);

	ImGui::Render();

	//ImGui_ImplCocos2dx_RenderDrawData(ImGui::GetDrawData());
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow *backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
