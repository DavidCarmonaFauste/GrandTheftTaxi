#include "Camera.h"



Camera::Camera(int width, int height, float zoom) {
	cameraRect_ = new SDL_Rect();
	cameraRect_->w = w_ = width;
	cameraRect_->h = h_ = height;
	cameraRect_->x = cameraRect_->y = 0;

	setZoom(zoom);
}


Camera::~Camera() {
	delete cameraRect_; cameraRect_ = nullptr;
}

void Camera::renderTexture(Texture * texture, SDL_Rect const & dest, SDL_Rect * clip, double angle) {
	SDL_Rect transposedRect = SDL_Rect();
	int width = 0, height = 0;
	SDL_RenderGetLogicalSize(Game::renderer_, &width, &height);

	transposedRect.w = (int) ( ((float)dest.w / (float)cameraRect_->w) * width);
	transposedRect.h = (int) ( ((float)dest.h / (float)cameraRect_->h) * height);
	transposedRect.x = (double)(dest.x - cameraRect_->x) * zoom_ / (cameraRect_->w / width);
	transposedRect.y = (double)(dest.y - cameraRect_->y) * zoom_ / (cameraRect_->h / height);
	texture->render(transposedRect, angle, clip);
}

void Camera::setPos(int x, int y, bool center) {
	cameraRect_->x = x;
	cameraRect_->y = y;

	if (center) {
		cameraRect_->x -= cameraRect_->w / 2;
		cameraRect_->y -= cameraRect_->h / 2;
	}
}

Vector2D Camera::getPos()
{
	return Vector2D(cameraRect_->x, cameraRect_->y);
}

void Camera::setSize(int w, int h, bool resetZoom) {
	cameraRect_->w = w_ = w;
	cameraRect_->h = h_ = h;

	if (resetZoom) zoom_ = 1;
	else setZoom(zoom_);
}

Vector2D Camera::getSize()
{
	return Vector2D(w_, h_);
}

void Camera::setZoom(float zoom, bool center) {
	zoom_ = zoom;

	cameraRect_->w = (int) (w_ * (1/zoom_));
	cameraRect_->h = (int) (h_ * (1/zoom_));

	if (center) {
		cameraRect_->x -= (cameraRect_->w - w_) / 2;
		cameraRect_->y -= (cameraRect_->h - h_) / 2;
	}
}

float Camera::getZoom() {
	return zoom_;
}