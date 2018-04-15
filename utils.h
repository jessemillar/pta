uint8_t angleToFrame(float angle, uint8_t frameCount)
{
	return (uint8_t)(angle / 360 * frameCount);
}

float normalizeAngle(float angle)
{
	angle = int(angle) % 360;

	if (angle < 0) angle += 360;

	return angle;
}

float findAngle(int x1, int y1, int x2, int y2)
{
	return atan2(y2 - y1, x1 - x2);
}

void drawGrid()
{
	uint8_t spacing = 100;

	// horizontal lines
	for (uint8_t y = 0; y < LEVEL_HEIGHT / spacing; y++)
	{
		arduboy.drawFastHLine(0, y * spacing - camera.y, 128, WHITE);
	}

	// vertical lines
	for (uint8_t x = 0; x < LEVEL_WIDTH / spacing; x++)
	{
		arduboy.drawFastVLine(x * spacing - camera.x, 0, 64, WHITE);
	}
}

void drawLocator(float xTarget, float yTarget, uint8_t width, uint8_t height)
{
	if (!camera.canSee(xTarget, yTarget, width, height))
	{
		int xLocator;
		int yLocator;

		// change coordinate space again to center of screen
		float xTargetCenter = xTarget - camera.x - 64;
		float yTargetCenter = yTarget - camera.y - 32;

		float slope = yTargetCenter / xTargetCenter;

		int padding = 3;
		int paddedWidth = 128 - padding * 2;
		int paddedHeight = 64 - padding * 2;

		// calculate indicator position if above or below
		if (yTargetCenter < 0) // top of screen
		{
			xLocator = (-1 * paddedHeight / 2) / slope;
			yLocator = -1 * paddedHeight / 2;
		}
		else // bottom of screen
		{
			xLocator = (paddedHeight / 2) / slope;
			yLocator = paddedHeight / 2;
		}

		//calculate indicator position if left or right
		if (xLocator < -1 * paddedWidth / 2) // left side
		{
			xLocator = -1 * paddedWidth / 2;
			yLocator = slope * -1 * paddedWidth / 2;
		}
		else if (xLocator > paddedWidth / 2) // right side
		{
			xLocator = paddedWidth / 2;
			yLocator = slope * paddedWidth / 2;
		}

		// change coordinate position back to original space
		xLocator += 64;
		yLocator += 32;

		// apply position
		arduboy.fillCircle(xLocator - 1, yLocator - 1, 2, WHITE);
	}
}
