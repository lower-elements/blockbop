#ifndef BBENGINE_AL_EXTENSIONS_EXTENSION_HPP
#define BBENGINE_AL_EXTENSIONS_EXTENSION_HPP

#include <type_traits>

#include <alc.h>

namespace openal {

template <class T>
concept FunctionPointer = std::is_invocable_v<T>;

class Extension {
public: // Member methods
  bool isSupported() const { return m_supported; }
  operator bool() const { return m_supported; }

protected:
  Extension(ALboolean is_supported);
  virtual ~Extension() {}

  virtual ALenum getEnum(const char *) const { return AL_NONE; }
  virtual void *getProcAddress(const char *) const { return nullptr; }

  /**
   * Convenience function to cast the function pointer to the right type
   * automatically
   */
  template <class T> void getFunction(const char *name, T *&val) const {
    val = (T *)(getProcAddress(name));
  }

private: // Member variable
  bool m_supported;
};

class AlcExtension : public Extension {
protected: // Member methods
  AlcExtension(ALCdevice *dev, const char *name);

  virtual ALenum getEnum(const char *) const override;
  virtual void *getProcAddress(const char *) const override;

protected: // Member variables
  ALCdevice *m_dev;
};

class AlExtension : public Extension {
protected: // Member methods
  AlExtension(const char *name);

  virtual ALenum getEnum(const char *) const override;
  virtual void *getProcAddress(const char *) const override;
};

} // namespace openal

#endif
