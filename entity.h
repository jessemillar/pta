struct Entity: Simple
{
	// TODO extract this from the compressed image
	unsigned char width = 0, height = 0;

	Rect cbox_conf = {.x = 0, .y = 0, .width = width, .height = height}; // used for cbox offset and size
	Rect cbox; // used to actually calculate collisions

	unsigned char ttl = 0;

	float angle = 0;
	float speed = 0;
	float maxSpeed = 2;

	void physics()
	{
		// apply momentum according to the current angle
		x += speed * cos(angle * 1000 / 57296);
		y -= speed * sin(angle * 1000 / 57296);

		// contain to the screen
		if (x < 0)
		{
			x = 0;
		}
		else if (x + width > camera.xMax)
		{
			x = camera.xMax - width;
		}

		// contain to the screen
		if (y < 0)
		{
			y = 0;
		}
		else if (y + height > camera.yMax)
		{
			y = camera.yMax - height;
		}
	}

	void updateCbox()
	{
		cbox = {.x = x + cbox_conf.x, .y = y + cbox_conf.y, .width = cbox_conf.width, .height = cbox_conf.height};
	}

	void collide(Rect other)
	{
		// preliminary solid collisions
		if (arduboy.collide(cbox, other))
		{
			float translateX = 0;
			float translateY = 0;

			// find x translation distance
			if (cbox.x < other.x)
			{
				translateX = (other.x - cbox_conf.width - cbox_conf.x + 1) - x;
			}
			else
			{
				translateX = (other.x + other.width - cbox_conf.x) - x;
			}

			// find y translation distance
			if (cbox.y < other.y)
			{
				translateY = (other.y - cbox_conf.height - cbox_conf.y + 1) - y;
			}
			else
			{
				translateY = (other.y + other.height - cbox_conf.y) - y;
			}

			// apply the translation
			if (abs(translateX) < abs(translateY))
			{
				x += translateX;
			}
			else
			{
				y += translateY;
			}
		}
	}
};
