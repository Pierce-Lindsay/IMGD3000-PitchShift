#pragma once
#include <SFML/Graphics.hpp>

namespace df {

	/// <summary>
	/// A class for a 32 bit (red, greem, blue, alpha channels) color.
	/// </summary>
	class Color {
	private:
		//store internal rgb
		uint8_t r; //red
		uint8_t g; //green
		uint8_t b; //blue
		uint8_t a; //alpha

		sf::Color sfml_color; //equivalent sfml color
		bool color_changed = false; //has the color changed since last sfml color update

	public:
		/// <summary>
		/// Returs te sfml color equivalent to this dragonfly color.
		/// </summary>
		sf::Color getSFMLColor();

		/// <summary>
		/// Create a new color based on a SFML color.
		/// </summary>
		Color(sf::Color sfml_color);

		/// <summary>
		/// Create a new color with rgba channels.
		/// </summary>
		Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);

		/// <summary>
		/// Get 8 bit red channel of color.
		/// </summary>
		uint8_t getR() const;

		/// <summary>
		/// Get 8 bit green channel of color.
		/// </summary>
		uint8_t getG() const;

		/// <summary>
		/// Get 8 bit blue channel of color.
		/// </summary>
		uint8_t getB() const;

		/// <summary>
		/// Get 8 bit alpha channel of color.
		/// </summary>
		uint8_t getA() const;

		/// <summary>
		/// Set 8 bit red channel of color.
		/// </summary>
		void setR(uint8_t r);

		/// <summary>
		/// Set 8 bit green channel of color.
		/// </summary>
		void setG(uint8_t g);

		/// <summary>
		/// Set 8 bit blue channel of color.
		/// </summary>
		void setB(uint8_t b);

		/// <summary>
		/// Set 8 bit alpha channel of color.
		/// </summary>
		void setA(uint8_t a);

		/// <summary>
		/// Tries to convert the given string to a pre-defined color, returns white if color not found.
		/// </summary>
		static df::Color colorFromString(std::string str_color);
	};


	extern const Color WHITE;
	extern const Color RED;
	extern const Color BLUE;
	extern const Color GREEN;
	extern const Color YELLOW;
	extern const Color ORANGE;
	extern const Color TURQUOISE;
	extern const Color GRAY;
	extern const Color PURPLE;
	extern const Color BLACK;
}