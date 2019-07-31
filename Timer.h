const int GLOBAL_TIME_FRAMES_PER_SECOND = 40;
const int GLOBAL_TIME_TICK_PER_FRAME = 1000 / GLOBAL_TIME_FRAMES_PER_SECOND;


class cTimer {
	public:
		cTimer();

		void getTick();
		void setDelay();

	private:
		Uint32 tickCount;
		Uint32 tickTest;
};