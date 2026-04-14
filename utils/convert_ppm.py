from PIL import Image
from pathlib import Path
import argparse
import time


def main() -> None:
	parser = argparse.ArgumentParser(description="Converte uma imagem PPM para PNG/JPG.")
	parser.add_argument("input", nargs="?", default="out.ppm", help="Arquivo PPM de entrada")
	parser.add_argument("output", nargs="?", help="Arquivo de saída (ex: imagem.png)")
	args = parser.parse_args()

	input_path = Path(args.input)
	if not input_path.exists():
		raise FileNotFoundError(f"Arquivo de entrada não encontrado: {input_path}")

	if args.output:
		output_path = Path(args.output)
		output_path.parent.mkdir(parents=True, exist_ok=True)
	else:
		nm = str(int(time.time()))
		output_path = Path("renders") / f"{nm}.jpg"
		output_path.parent.mkdir(parents=True, exist_ok=True)

	im = Image.open(input_path)
	im.save(output_path)


if __name__ == "__main__":
	main()
