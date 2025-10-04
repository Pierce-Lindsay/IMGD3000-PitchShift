#pragma once
#include "../Vector.h"
#include "../Event.h"
#include "../graphics/Animation.h"
#include "../Box.h"
#include <string>

namespace df {

	/// <summary>
	/// Helps determine what objects can collide with eachother.
	/// Hard collide with hard, Spectral cannot collide, Softs objects collide
	/// but dont impede eachother.
	/// </summary>
	enum class Solidness
	{
		HARD, //impede who ever is moving
		SOFT, //don't impede but still can collide
		SPECTRAL, //no collisions
	};

	/// <summary>
	/// A class for handling all GameObjects in the engine. An arbitrary high-level object to inherit from.
	/// </summary>
	class Object
	{
	private:
		int id; //unique identifier
		std::string type = "undefined"; //user-defined type
		Solidness solidness = Solidness::HARD; //hard by default
		Vector pos; //2d pos
		Vector v_direction; //2d veclocity direction vector
		float speed = 0; //speed of object exists in case speed set with 0, 0 vector
		bool marked_for_delete = false;
		unsigned int altitude;
		Animation animation;
		Box collision_box;


	public:
		/// <summary>
		/// Create a new object with default attributes (0, 0) position, size 1 collision box, undefined type, id
		/// </summary>
		Object();

		/// <summary>
		/// Delete object and handle dependencies.
		/// </summary>
		virtual ~Object();

		/// <summary>
		/// Set the object's id.
		/// </summary>
		void setID(int new_id);

		/// <summary>
		/// Get the object's id.
		/// </summary>
		/// <returns></returns>
		int getID() const;

		/// <summary>
		/// Set the object's subclass type.
		/// </summary>
		void setType(std::string new_type);

		/// <summary>
		/// Get the objects subclass type.
		/// </summary>
		std::string getType() const;

		/// <summary>
		/// Set the position of the object to be equal to this vector.
		/// </summary>
		void setPosition(Vector new_pos);

		/// <summary>
		/// Set the velocity of the object to be equal to this vector.
		/// </summary>
		void setVelocity(Vector new_velocity);


		/// <summary>
		/// Get the position of the object as a vector.
		/// </summary>
		Vector getPosition() const;

		/// <summary>
		/// Get the velocity of the object as a vector.
		/// </summary>
		Vector getVelocity() const;

		/// <summary>
		/// Get the speed of the object as a scaler.
		/// </summary>
		float getSpeed() const;

		/// <summary>
		/// Set the direction of the object's velocity as a vector. If input vector is not normal,
		/// it is normalized.
		/// </summary>
		void setDirection(Vector unit_vector);

		/// <summary>
		/// Get the direction of the velocity of the object.
		/// </summary>
		Vector getDirection() const;

		/// <summary>
		///	Returns the position of the object after adding the velocity to teh current position.
		/// </summary>
		Vector predictPosition() const;

		/// <summary>
		/// Set the speed of the object as a scaler.
		/// </summary>
		void setSpeed(float new_speed);

		/// <summary>
		/// Set this object internally as something that will be deleted soon.
		/// </summary>
		void setMarkForDelete(bool b);

		/// <summary>
		/// Get whether thos object wis marked to be deleted.
		/// </summary>
		bool getMarkForDelete() const;

		/// <summary>
		/// Handle event (default ignores everything).
		/// </summary>
		/// <returns>0 if igored, 1 if handled.</returns>
		virtual int eventHandler(const Event* p_e);

		/// <summary>
		/// Draw the object to the display.
		/// </summary>
		virtual int draw();

		/// <summary>
		/// Get the rendering altitude for this object, lowest is furthest back, highest
		/// is furthest towards the screen.
		/// </summary>
		int getAltitude() const;

		/// <summary>
		/// Sets the rendering altitude for this object, lowest is furthest back, highest
		/// is furthest towards the screen. Accepted values between MIN_ALTITUDE and MAX_ALTITUDE
		/// </summary>
		/// <returns>Returns 0 if accepted value, -1 else.</returns>
		int setAltitude(int new_altitude);

		/// <summary>
		/// Set the solidness of this object.
		/// </summary>
		void setSolidness(Solidness solid);

		/// <summary>
		/// Get the solidness of this object.
		/// </summary>
		Solidness getSolidness() const;

		/// <summary>
		/// Determines if object experiences collisions.
		/// </summary>
		/// <returns>True if solid or soft, false if spectral.</returns>
		bool isSolid() const;

		/// <summary>
		/// Get the current sprite pointer of this object.
		/// </summary>
		Sprite* getSprite() const;

		/// <summary>
		/// Set the sprite of this object with the given label, found from the recouurce managers, sprites_map.
		/// </summary>
		/// <param name="sprite_label"></param>
		/// <returns>0 if successful, -1 if sprite with label not found.</returns>
		int setSprite(std::string sprite_label);

		/// <summary>
		/// Get the object's collision box.
		/// </summary>
		Box getBox() const;

		/// <summary>
		/// Set the object's collision box.
		/// </summary>
		void setBox(Box box);
	};
}