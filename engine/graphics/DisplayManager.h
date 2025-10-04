#pragma once
#include "../Manager.h"
#include "../Vector.h"
#include "Color.h"
#include "Justification.h"
#include <SFML/Graphics.hpp>

#define DM df::DisplayManager::GetInstance()
namespace df {

	//SFML window defaults
	const int MAX_ALTITUDE = 4;
	const int MIN_ALTITUDE = 0;
	const unsigned int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const unsigned int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const unsigned int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const unsigned int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const unsigned int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar | sf::Style::Close;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DFAULT = "df-font.ttf";
	const std::string FONTS_DIRECTORY = "assets/fonts/";

	/// <summary>
	/// A class for managing the display of the game. Uses SFML with text based graphics.
	/// </summary>
	class DisplayManager : public Manager
	{
	private:
		//singleton stuff
		DisplayManager();
		DisplayManager(DisplayManager const& copy);
		void operator=(DisplayManager const& assign);

		sf::Font m_font; //font for ascii graphics
		sf::RenderWindow* m_p_window = NULL; //SFML window
		unsigned int m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT; //current window width pixels
		unsigned int m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT; //current window height pixels
		unsigned int m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT; //current window width chars
		unsigned int m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT; //current window height chars


	public:
		/// <summary>
		/// Destroys the game and any other dependencies.
		/// </summary>
		~DisplayManager();

		/// <summary>
		/// Get instance of the one and only DisplayManager.
		/// </summary>
		/// <returns></returns>
		static DisplayManager& GetInstance();

		/// <summary>
		/// Start up DisplayManager and required dependencies.
		/// </summary>
		/// <returns>0 if successful.</returns>
		int startUp() override;

		/// <summary>
		/// Shut down DisplayManager and required dependencies.
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Draw a specified character at the screen location (world_pos Vector) with the specified color.
		/// </summary>
		/// <returns>0 if good, -1 else.</returns>
		int drawCh(Vector world_pos, char ch, Color color = WHITE) const;

		/// <summary>
		/// Draw a specified string at the screen location (world_pos Vector) with the 
		/// specified color and justification.
		/// Justification with respect to position.
		/// </summary>
		///	<returns>0 if good, -1 else.</returns>
		int drawString(Vector world_pos, std::string string, Justification just, Color color = WHITE) const;

		/// <summary>
		/// Get the horizontal character width of the window.
		/// </summary>
		int getHorizontalChars() const;

		/// <summary>
		/// Get the vertical character height of the window.
		/// </summary>
		int getVerticalChars() const;

		/// <summary>
		/// Get the horizontal pixel width of the window.
		/// </summary>
		int getHorizontalPixels() const;

		/// <summary>
		/// Get the vertical pixel height of the window.
		/// </summary>
		int getVerticalPixels() const;

		/// <summary>
		/// Renders the current display buffer.
		/// </summary>
		/// <returns>0 if good, -1 else.</returns>
		int swapBuffers();

		/// <summary>
		/// Get a pointer to the SFML window.
		/// </summary>
		sf::RenderWindow* getWindow() const;
	};
}