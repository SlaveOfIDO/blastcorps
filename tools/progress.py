import json
import anybadge
import os

# ----------------------------
# Configuration
# ----------------------------
INPUT_FILE = "report.json"
OUTPUT_DIR = "badges"

# Color thresholds (percentage values)
THRESHOLDS = {
    20: "red",
    40: "orange",
    60: "yellow",
    80: "green",
    90: "brightgreen"
}

DEFAULT_COLOR = "lightgrey"


# ----------------------------
# Helpers
# ----------------------------
def load_report(path):
    with open(path, "r") as f:
        return json.load(f)


def create_badge(label, percent, output_path):
    """
    Create a badge using numeric thresholds (for coloring)
    and display a formatted percentage string.
    """
    badge = anybadge.Badge(
        label=label,
        value=percent,          # numeric value for thresholds
        thresholds=THRESHOLDS,
        default_color=DEFAULT_COLOR,
        value_format="%.2f%%"   # ensures display like "52.24%"
    )
    badge.write_badge(output_path, overwrite=True)


# ----------------------------
# Main logic
# ----------------------------
def main():
    data = load_report(INPUT_FILE)

    # Ensure output directory exists
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # ---- Total badge ----
    total_percent = data.get("measures", {}).get("matched_code_percent", 0.0)

    total_path = os.path.join(OUTPUT_DIR, "total.svg")
    create_badge("Blast Corps (us.v11)", total_percent, total_path)
    print(f"Created total badge: {total_path}")

    # ---- Category badges ----
    for category in data.get("categories", []):
        cat_id = category.get("id", "unknown")
        measures = category.get("measures", {})

        # Default to 0.0 if missing
        percent = measures.get("matched_code_percent", 0.0)

        filename = f"{cat_id}.svg"
        output_path = os.path.join(OUTPUT_DIR, filename)

        create_badge(cat_id, percent, output_path)
        print(f"Created badge: {output_path} (value: {percent:.2f}%)")


# ----------------------------
# Entry point
# ----------------------------
if __name__ == "__main__":
    main()