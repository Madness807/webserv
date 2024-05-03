#include "MimeTypeManager.hpp"

void MimeTypeManager::initMimeTypes() {
    
    mimeTypes[".html"] = "text/html; charset=UTF-8";
	mimeTypes[".css"] = "text/css; charset=UTF-8";
	mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".jpeg"] = "image/jpeg";
	mimeTypes[".png"] = "image/png";
}

std::string MimeTypeManager::getMimeType(const std::string& extension) const {
    auto it = _mimeTypes.find(extension);
    if (it != _mimeTypes.end()) {
        return it->second;
    }
    return "application/octet-stream"; // Type MIME par défaut
}