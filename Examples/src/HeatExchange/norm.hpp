double norm (std::string Norm, double xn, double xv, double h, double xpsn, double xpso){
	// Rn norm
	if (Norm.compare("Rn")==0){
		return (xn-xv)*(xn-xv);
	}
	
	else {
		// L2 norm
		if (Norm.compare("L2")==0){
			return(xn-xv)*(xn-xv)*h;
		}
		// H1 norm
		if (Norm.compare("H1")==0){
			return (-(xn-xv)*(xn-xv)*h) + ((xpsn-xpso)*(xpsn-xpso)/h);
		}
	}
}