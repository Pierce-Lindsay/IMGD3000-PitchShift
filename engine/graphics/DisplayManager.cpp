#include "DisplayManager.h"
#include "../LogManager.h"
#include "../Utility.h"

using namespace df;

DisplayManager::DisplayManager()
{
	setType("DisplayManager");
}

DisplayManager::~DisplayManager()
{
}


DisplayManager& DisplayManager::GetInstance()
{
	static DisplayManager dm;
	return dm;
}


int DisplayManager::startUp()
{
	if (!LM.isStarted())
	{
		if (LM.startUp() == -1)
			return -1;
	}

	if (m_p_window != NULL && isStarted()) // already started?
	{
		LM.writeLog("DisplayManager::startUp::Start up exited early because display manager is already started.");
		return Manager::startUp();
	}

	//start up SFML window and text
	std::string font_path = FONTS_DIRECTORY + FONT_FILE_DFAULT;
	if (m_font.openFromFile(font_path) == false)
	{
		LM.writeLog("DisplayManager::startUp::Unable to load font file with path: %s!", font_path);
		return -1;
	}
	//window
	m_p_window = new sf::RenderWindow(sf::VideoMode({ m_window_horizontal_pixels, m_window_vertical_pixels }), 
		WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

	if (!m_p_window)
	{
		LM.writeLog("DisplayManager::startUp::Failed to allocate for SFML render window.");
		return -1;
	}

	m_p_window->setMouseCursorVisible(false);
	m_p_window->setVerticalSyncEnabled(true); //vsync on for now

	float char_width = charWidth();
	float char_height = charHeight();

	m_rectangle.setSize(sf::Vector2f(char_width, char_height - 1)); //not sure what -1 for
	m_rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	m_rectangle.setPosition(sf::Vector2f(0, 0)); //default for now);

	m_text = new sf::Text(m_font);
	m_text->setStyle(sf::Text::Bold); // bold looks better


	//text we're drawing

	int text_size = char_width * 2; //looks good i guess
	if (char_width >= char_height)
		text_size = char_height * 2;

	m_text->setCharacterSize(text_size);
	m_text->setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);

	LM.writeLog("DisplayManager::startUp::Started DisplayManager Successfully!");

	return Manager::startUp();
}

void DisplayManager::shutDown()
{
	if (m_p_window != NULL)
	{
		delete m_text;
		m_text = NULL;
		m_p_window->close();
		delete m_p_window;
		m_p_window = NULL;
	}
	LM.writeLog("DisplayManager::shutDown::shutdown DisplayManager Successfully!");
	Manager::shutDown();
}


int DisplayManager::drawCh(Vector world_pos, char ch, Color color)
{
	if (m_p_window == NULL)
	{
		LM.writeLog("DisplayManager::drawCh::Failed to draw because window was NULL!");
		return -1;
	}
	//convert chars coords to pixel coords
	Vector pixel_pos = spacesToPixels(world_pos);
	float char_width = charWidth();
	float char_height = charHeight();
	//create rectangles behind characters for "see through" text
	m_rectangle.setPosition(sf::Vector2f(pixel_pos.x + char_width / 10,
		pixel_pos.y + char_height / 5)); //for centering, looks good??
	m_p_window->draw(m_rectangle);

	//text we're drawing

	m_text->setString(ch);
	m_text->setFillColor(color.getSFMLColor());
	m_text->setPosition(sf::Vector2f(pixel_pos.x, pixel_pos.y));

	m_p_window->draw(*m_text);
	return 0;
}

int DisplayManager::drawString(Vector world_pos, std::string string, Justification just, Color color)
{
	if (m_p_window == NULL)
	{
		LM.writeLog("DisplayManager::drawString::Failed to draw because window was NULL!");
		return -1;
	}
		
	//convert chars coords to pixel coords
	Vector pixel_pos = spacesToPixels(world_pos);
	float offset = -1 *float(string.size()) * charWidth();

	if (just == Justification::RIGHT)
		offset = 0;
	else if (just == Justification::CENTER)
		offset *= 0.5;

	pixel_pos.x += offset;
	drawCh(pixelsToSpaces(pixel_pos), string[0], color);
	for (int i = 1; i < string.size(); i++)
	{
		pixel_pos.x += charWidth();
		drawCh(pixelsToSpaces(pixel_pos), string[i], color);
	}
	return 0;
}


int DisplayManager::getHorizontalChars() const
{
	return m_window_horizontal_chars;
}


int DisplayManager::getVerticalChars() const
{
	return m_window_vertical_chars;
}


int DisplayManager::getHorizontalPixels() const
{
	return m_window_horizontal_pixels;
}


int DisplayManager::getVerticalPixels() const
{
	return m_window_vertical_pixels;
}


int DisplayManager::swapBuffers() //display the frame
{
	if (m_p_window == NULL)
	{
		LM.writeLog("DisplayManager::swapBuffers::Failed to swap because window was NULL!");
		return -1;
	}	

	m_p_window->display(); //display drawing
	m_p_window->clear(); //clear the drawings
	return 0;
}


sf::RenderWindow* DisplayManager::getWindow() const
{
	return m_p_window;
}