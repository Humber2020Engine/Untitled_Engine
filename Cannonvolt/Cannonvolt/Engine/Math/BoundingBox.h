#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox {
public:

	//x = Width, y = Height
	glm::vec2 dimentions;

	glm::vec2 pos;

	inline BoundingBox() {
		dimentions = glm::vec2();
		pos = glm::vec2();
	}

	inline BoundingBox(glm::vec2 dimentions_, glm::vec2 pos_) {
		dimentions = dimentions_;
		pos = pos_;
	}

	//Is not in collision because Screen partition could not access it

	//Both maxs must be larger the the others mins
	inline bool Intersects(BoundingBox* box_) {

		glm::vec2 maxCorner = pos + dimentions;

		glm::vec2 otherMinCorner = box_->pos;
		glm::vec2 otherMaxCorner = box_->pos + box_->dimentions;

		//Self intersect prevention
		if (pos == otherMinCorner && maxCorner == otherMaxCorner) { return false; }

		if (pos.x <= otherMaxCorner.x && otherMinCorner.x <= maxCorner.x  &&
			pos.y <= otherMaxCorner.y && otherMinCorner.y <= maxCorner.y) {
			return true;
		}

		return false;
	}

	//Get the shortest distance to sperating two objects
	inline glm::vec2 CollisionDepth(BoundingBox* box_) {

		glm::vec2 maxCorner = pos + dimentions;

		glm::vec2 otherMinCorner = box_->pos;
		glm::vec2 otherMaxCorner = box_->pos + box_->dimentions;

		glm::vec2 depth(0);

		//First get which side is colliding

		//Coming from the right
		float x1 = maxCorner.x - otherMinCorner.x;

		//Coming from the left
		float x2 = otherMaxCorner.x - pos.x;


		//Coming from the top
		float y1 = maxCorner.y - otherMinCorner.y;

		//Coming from the bottom
		float y2 = otherMaxCorner.y - pos.y;

		x1 < x2 ? depth.x = -x1 - 0.4f : depth.x = x2 + 0.4f;

		y1 < y2 ? depth.y = -y1 - 0.4f : depth.y = y2 + 0.4f;

		depth.x < depth.y ? depth.y = 0 : depth.x = 0;
		
		return depth;
	}
};



#endif // !BOUNDINGBOX_H
