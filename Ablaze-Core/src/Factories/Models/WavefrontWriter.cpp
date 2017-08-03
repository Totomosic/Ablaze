#include "WavefrontWriter.h"
#include "Log.h"

namespace Ablaze
{
	namespace Internal
	{

		void WriteVertex(WavefrontFile* file, float x, float y, float z)
		{
			file->WriteLine("v " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
		}

		void WriteNormal(WavefrontFile* file, float x, float y, float z)
		{
			file->WriteLine("vn " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
		}

		void WriteTexCoord(WavefrontFile* file, float x, float y)
		{
			file->WriteLine("vt " + std::to_string(x) + " " + std::to_string(y));
		}

		void WriteFace(WavefrontFile* file, int64 v1, int64 v2, int64 v3)
		{
			String v1S = std::to_string(v1 + 1);
			String v2S = std::to_string(v2 + 1);
			String v3S = std::to_string(v3 + 1);
			file->WriteLine("f " + v1S + "/" + v1S + "/" + v1S + " " + v2S + "/" + v2S + "/" + v2S + " " + v3S + "/" + v3S + "/" + v3S);
		}

		void AdvancePointer(float* ptr, int amount)
		{
			byte* b = (byte*)ptr;
			b += amount;
			ptr = (float*)b;
		}

		void WavefrontWriter::WriteToFile(WavefrontFile* file, Model* model)
		{
			// TODO: optimize this
			file->Open(OpenMode::Write);
			file->Clear();
			VBO* vbo = model->GetVAO()->GetAttribute(0);
			IndexBuffer* ibo = model->GetVAO()->GetIndexBuffer();
			int64 length = vbo->GetSize() / sizeof(float);
			int64 indexCount = ibo->GetSize() / sizeof(uint);
			float* data = (float*)vbo->MapBuffer(Access::Read);
			uint* indices = (uint*)ibo->MapBuffer(Access::Read);

			const BufferLayout& layout = vbo->GetLayout();

			for (int i = 0; i < length; i += layout.GetStride() / sizeof(float))
			{
				WriteVertex(file, data[i + 0], data[i + 1], data[i + 2]);
				WriteNormal(file, data[i + 3], data[i + 4], data[i + 5]);
				WriteTexCoord(file, data[i + 6], data[i + 7]);
			}
			file->WriteLine("");
			for (int i = 0; i < indexCount; i += 3)
			{
				WriteFace(file, indices[i + 0], indices[i + 1], indices[i + 2]);
			}

			file->Close();

			ibo->UnmapBuffer();
			vbo->UnmapBuffer();
		}

	}
}