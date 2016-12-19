#pragma once

struct Vector {
	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;

	Vector(float X = 0, float Y = 0, float Z = 0) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	Vector operator + (const Vector& input) {
		return Vector(this->X + input.X, this->Y + input.Y, this->Z + input.Z);
	}

	Vector operator - (const Vector& input) {
		return Vector(this->X - input.X, this->Y - input.Y, this->Z - input.Z);
	}

	Vector operator * (const Vector& input) {
		return Vector(this->X * input.X, this->Y * input.Y, this->Z * input.Z);
	}

	Vector operator / (const Vector& input) {
		return Vector(this->X / input.X, this->Y / input.Y, this->Z / input.Z);
	}
};

typedef Vector QAngle;