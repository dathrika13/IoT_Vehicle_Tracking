# Contributing to IoT Vehicle Tracking System

First off, thank you for considering contributing to this project! 🎉

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [Pull Requests](#pull-requests)
- [Style Guidelines](#style-guidelines)
- [Commit Messages](#commit-messages)

## Code of Conduct

This project and everyone participating in it is governed by our Code of Conduct. By participating, you are expected to uphold this code. Please report unacceptable behavior to the project maintainers.

## How Can I Contribute?

### Reporting Bugs

Before creating bug reports, please check the existing issues to avoid duplicates. When you create a bug report, include as many details as possible:

**Bug Report Template:**

```markdown
**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Go to '...'
2. Click on '....'
3. See error

**Expected behavior**
A clear and concise description of what you expected to happen.

**Screenshots**
If applicable, add screenshots to help explain your problem.

**Hardware Setup:**
 - NodeMCU Version: [e.g., ESP-12E]
 - GPS Module: [e.g., NEO-6M]
 - Other components: [list them]

**Software:**
 - Arduino IDE Version: [e.g., 1.8.19]
 - ESP8266 Board Package Version: [e.g., 3.0.2]
 - Library Versions: [list relevant libraries]

**Additional context**
Add any other context about the problem here.
```

### Suggesting Enhancements

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion, include:

- **Use a clear and descriptive title**
- **Provide a detailed description** of the suggested enhancement
- **Explain why this enhancement would be useful**
- **List any additional hardware/software** that might be required

### Pull Requests

1. **Fork** the repository
2. **Clone** your fork locally
3. **Create a branch** for your feature (`git checkout -b feature/amazing-feature`)
4. **Make your changes**
5. **Test** your changes thoroughly
6. **Commit** your changes with a descriptive message
7. **Push** to your branch (`git push origin feature/amazing-feature`)
8. **Open a Pull Request**

#### Pull Request Checklist

- [ ] Code compiles without errors
- [ ] Tested on actual hardware (if possible)
- [ ] Updated documentation (if needed)
- [ ] Added comments for complex code sections
- [ ] Followed the code style guidelines

## Style Guidelines

### Arduino/C++ Code Style

```cpp
// Use descriptive variable names
int sensorValue;          // Good
int sv;                   // Bad

// Constants in UPPER_CASE
const int LED_PIN = 13;

// Functions in camelCase
void readSensorData() {
    // Code here
}

// Use comments to explain complex logic
// Calculate distance using the Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Implementation
}

// Indent with 2 spaces (Arduino IDE default)
void setup() {
  Serial.begin(115200);
  if (condition) {
    // Do something
  }
}
```

### Documentation Style

- Use Markdown for documentation
- Include code examples where appropriate
- Keep explanations clear and concise
- Add images/diagrams when they help explain concepts

## Commit Messages

Write clear and meaningful commit messages:

```
✅ Good:
- Add GPS timeout error handling
- Fix WiFi reconnection bug
- Update README with circuit diagram
- Refactor sensor reading functions

❌ Bad:
- Fixed stuff
- Updates
- asdfgh
- WIP
```

### Commit Message Format

```
<type>: <subject>

<body (optional)>

<footer (optional)>
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, etc.)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

**Example:**
```
feat: Add geofencing capability

Implemented geofencing feature that alerts when vehicle
exits predefined boundary. Uses circular geofence with
configurable radius.

Closes #42
```

## Questions?

Feel free to open an issue with your question or contact the maintainers directly.

---

Thank you for contributing! 🙏
