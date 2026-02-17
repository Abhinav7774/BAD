namespace BAD {
	_declspec(dllimport) void Print();
}

void main() {
	BAD::Print();
}