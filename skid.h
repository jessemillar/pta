struct Skid: Simple
{
	Skid(float X, float Y, int CurFrame)
	{
		x = X, y = Y;

		curFrame = CurFrame;

		ttl = 20;
	}

	void update()
	{
		ttl--;
	}

	void draw()
	{
		sprites.drawPlusMask(x - camera.x, y - camera.y, dust_plus_mask, curFrame);
	}
};
