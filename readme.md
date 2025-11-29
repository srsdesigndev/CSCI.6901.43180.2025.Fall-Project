# Peer Study Matching System

Simple C++ program to match students into study groups.

## Files Needed

1. `student_matcher.cpp` - Main program (all code in one file)
2. `json.hpp` - JSON library (download below)
3. `run.sh` - Run script

## Setup

**Step 1:** Download json.hpp
```
https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
```

**Step 2:** Put all 3 files in same folder

**Step 3:** Run
```bash
chmod +x run.sh
./run.sh
```

## Features

- **Enroll students** with learning profiles
- **Generate groups** based on compatibility
- **Update profiles** anytime
- **View statistics**
- Data saves to JSON files

## Usage

1. Choose option 1 to enroll students
2. Choose option 5 to generate groups
3. Choose option 6 to view your group

All data saves automatically in `students.json` and `groups.json`

## Troubleshooting

**"json.hpp not found"**
→ Download it and put in same folder

**"permission denied"**
→ Run `chmod +x run.sh`

**"g++ not found"**
→ Install: `brew install gcc` (Mac) or install Xcode tools

## Manual Compile

```bash
g++ -std=c++11 -o student_matcher student_matcher.cpp
./student_matcher
```
